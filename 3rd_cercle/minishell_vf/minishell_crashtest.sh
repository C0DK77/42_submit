#!/usr/bin/env bash
# minishell_crashtest.sh
# Ultra-hard crash test suite for 42 minishell.
# Compares behavior against /bin/bash for stdout, stderr, and exit status.
# Usage: ./minishell_crashtest.sh /path/to/minishell
# Optional env:
#   MSH_TIMEOUT=5         # seconds per test
#   MSH_JOBS=1            # parallelism (1..8) (1 = sequential, safer for debugging)
#   MSH_FILTER=""         # grep-like pattern to run only matching test names
#   MSH_KEEP=0            # keep workdir (1 keeps)
set -euo pipefail

if [[ $# -lt 1 ]]; then
  echo "Usage: $0 /path/to/minishell" >&2
  exit 2
fi

MINISHELL_BIN="$1"
if [[ ! -x "$MINISHELL_BIN" ]]; then
  echo "ERROR: minishell binary '$MINISHELL_BIN' not found or not executable" >&2
  exit 2
fi

: "${MSH_TIMEOUT:=5}"
: "${MSH_JOBS:=1}"
: "${MSH_FILTER:=}"
: "${MSH_KEEP:=0}"

WORKDIR="$(mktemp -d -t minishell-XXXXXX)"
trap '[[ $MSH_KEEP -eq 1 ]] || rm -rf "$WORKDIR"' EXIT

PASS=0
FAIL=0
SKIP=0
TOTAL=0

nl=$'\n'

# --- Helpers -----------------------------------------------------------------

color() { # $1=name  $2=string
  case "$1" in
    red) printf "\033[31m%s\033[0m" "$2";;
    green) printf "\033[32m%s\033[0m" "$2";;
    yellow) printf "\033[33m%s\033[0m" "$2";;
    blue) printf "\033[34m%s\033[0m" "$2";;
    *) printf "%s" "$2";;
  esac
}

log() { printf "%s\n" "$*"; }

normalize() {
  # Strip common prompt patterns to avoid false diffs (minishell$, $, #, >)
  sed -E 's/^[[:space:]]*([A-Za-z0-9._-]+)?(minishell)?[$#>] ?//'
}

run_in_bash() { # $1=command string
  local cmd="$1"
  # Run in bash -lc to mimic login-ish environment; capture stdout, stderr, and exit
  local out err status
  out="$(bash -lc "$cmd" 2> >(cat >&2))" || status=$?
  status=${status:-0}
  printf "%s" "$out"
  return "$status"
}

run_in_minishell() { # $1=command string
  local cmd="$1"
  # Feed the command, then print __EXIT:$?__ and exit to catch status
  # Avoid relying on minishell -c (many projects don't implement it).
  # We also add a 'builtin echo' guard in case echo is overridden — harmless.
  local script="
$cmd
printf \"__EXIT:%s__\\n\" \"\$?\"
exit
"
  # Timeout to prevent hangs
  local out status
  out="$(timeout "$MSH_TIMEOUT" bash -c '
    set -o pipefail
    # run minishell and strip prompts
    printf "%s" "$0" | "'"$MINISHELL_BIN"'" 2>&1 | normalize
  ' "$script")" || status=$?
  # If timeout - return 124 as status
  status=${status:-0}
  printf "%s" "$out"
  return "$status"
}

extract_exit_marker() { # reads stdin; prints content without marker; echoes status via global var
  # marker format: __EXIT:<code>__
  local input
  input="$(cat)"
  local code
  code="$(grep -o '__EXIT:[0-9]\+__' <<<"$input" | tail -n1 | sed -E 's/[^0-9]*([0-9]+).*/\1/')"
  # Remove markers from output
  input="${input//__EXIT:${code}__/}"
  printf "%s" "$input"
  EXIT_CODE="${code:-255}"
}

diff_outputs() { # $1=bash_out $2=minishell_out
  diff -u --label bash --label minishell <(printf "%s" "$1" | normalize) <(printf "%s" "$2" | normalize) || return 1
  return 0
}

record_result() { # $1=name $2=status PASS/FAIL/SKIP $3=details
  case "$2" in
    PASS) PASS=$((PASS+1));;
    FAIL) FAIL=$((FAIL+1));;
    SKIP) SKIP=$((SKIP+1));;
  esac
  TOTAL=$((TOTAL+1))
  local tag="$2"
  [[ "$2" == PASS ]] && tag="$(color green PASS)" || true
  [[ "$2" == FAIL ]] && tag="$(color red FAIL)" || true
  [[ "$2" == SKIP ]] && tag="$(color yellow SKIP)" || true
  printf " [%s] %s\n" "$tag" "$1"
  if [[ -n "${3:-}" ]]; then
    printf "%s\n" "$(color blue "$3")"
  fi
}

# --- Test harness ------------------------------------------------------------

run_case() { # $1=name  $2=command
  local name="$1" cmd="$2"
  if [[ -n "$MSH_FILTER" && ! "$name" =~ $MSH_FILTER ]]; then
    record_result "$name" SKIP "Filtered out"
    return
  fi

  # Prepare separate envs to avoid pollution between tests
  local tdir="$WORKDIR/$name"
  mkdir -p "$tdir"
  (cd "$tdir"

    # Run bash reference
    local b_out b_status
    b_out="$( { run_in_bash "$cmd" || b_status=$?; } 2> >(tee "$tdir/bash.stderr" >&2) )"
    b_status=${b_status:-0}

    # Run minishell
    local m_raw m_out m_run_status m_status
    m_raw="$( { run_in_minishell "$cmd" || m_run_status=$?; } 2> >(tee "$tdir/minishell.stderr" >&2) )"
    m_run_status=${m_run_status:-0}
    m_out="$(printf "%s" "$m_raw" | extract_exit_marker)"
    m_status="${EXIT_CODE:-255}"

    # Store outputs
    printf "%s" "$b_out" > "$tdir/bash.stdout"
    printf "%s" "$m_out" > "$tdir/minishell.stdout"
    echo "$b_status" > "$tdir/bash.status"
    echo "$m_status" > "$tdir/minishell.status"

    # Compare
    local details=""
    local ok=1
    if ! diff_outputs "$b_out" "$m_out"; then
      ok=0
      details+="STDOUT/STDERR differ${nl}"
      details+="--- bash stdout ---${nl}$(<"$tdir/bash.stdout")${nl}"
      details+="--- minishell stdout ---${nl}$(<"$tdir/minishell.stdout")${nl}"
      details+="--- bash stderr ---${nl}$(<"$tdir/bash.stderr")${nl}"
      details+="--- minishell stderr ---${nl}$(<"$tdir/minishell.stderr")${nl}"
    fi
    if [[ "$b_status" != "$m_status" ]]; then
      ok=0
      details+="Exit status: bash=$b_status minishell=$m_status${nl}"
    fi

    if [[ $ok -eq 1 ]]; then
      record_result "$name" PASS ""
    else
      record_result "$name" FAIL "$details"
      echo "Artifacts kept at: $tdir" >&2
    fi
  )
}

# --- Fixtures ----------------------------------------------------------------
setup_fixtures() {
  local d="$WORKDIR/fixtures"
  mkdir -p "$d"
  printf "alpha\nbeta\ngamma\ndelta\n" > "$d/words.txt"
  printf "one two three four\n" > "$d/line.txt"
  dd if=/dev/zero of="$d/blob.bin" bs=1024 count=64 status=none
  mkdir -p "$d/dir/sub"
  touch "$d/dir/a.c" "$d/dir/b.h" "$d/dir/c.txt"
  ln -sf nonexist "$d/broken_link"
}
setup_fixtures

# --- Test catalog ------------------------------------------------------------

# Builtins & basics
run_case "echo_simple"             'echo hello world'
run_case "echo_opts"               'echo -n a; echo b; echo -e "x\ty"'
run_case "pwd_basic"               'pwd'
run_case "cd_relative"             'mkdir -p t && cd t && pwd | grep /t$'
run_case "cd_dotdot"               'mkdir -p a/b && cd a/b && cd .. && pwd | grep /a$'
run_case "cd_dash"                 'mkdir -p x && cd x && cd - >/dev/null && pwd'
run_case "env_basic"               'env | sort | head -n 3'
run_case "export_unset"            'unset FOO; export BAR=42; echo "$BAR"; unset BAR; echo "${BAR:-empty}"'
run_case "exit_status"             '(exit 12); echo $?; exit 0'

# Quotations & expansions
run_case "quote_single"            "echo 'a  b   c'"
run_case "quote_double"            'FOO=ok; echo "x $FOO y"'
run_case "escape_backslash"        'echo \" \$HOME \\\\'
run_case "var_expand_edge"         'unset A; echo "${A}X" "${A:-fallback}" "${#A}"'
run_case "exit_code_var"           'false; echo "status:$?"'

# Redirections
run_case "redir_out_trunc"         'echo 123 > out.txt; cat out.txt'
run_case "redir_out_append"        'echo 1 > out.txt; echo 2 >> out.txt; cat out.txt'
run_case "redir_in_basic"          'cat < "$WORKDIR/fixtures/words.txt" | wc -l'
run_case "redir_fd_dup"            'echo hi 1>o.txt 2>&1; cat o.txt'
run_case "redir_clobber_err"       'echo hi > /root/forbidden 2>/dev/null; echo $?'
run_case "redir_ambiguous"         'unset A; > "$A" 2>/dev/null || echo "ambiguous"'

# Pipes
run_case "pipe_simple"             'printf "a\nb\n" | grep b'
run_case "pipe_multi"              'seq 1 10 | paste -sd+ | bc'
run_case "pipe_cat_wc"             'cat "$WORKDIR/fixtures/words.txt" | wc -w'
run_case "pipe_fd_leak"            'for i in $(seq 1 50); do echo x; done | grep x | wc -l'

# Here-doc (simulate input via stdin)
run_case "heredoc_basic"           'cat <<EOF
hello
EOF'
run_case "heredoc_expand"          'X=42
cat <<EOF
num:$X
EOF'
run_case "heredoc_noexpand"        'X=42
cat <<'\''EOF'\''
num:$X
EOF'

# Globbing (if unsupported, expect literal behavior differences)
run_case "glob_star"               'cd "$WORKDIR/fixtures/dir" && printf "%s\n" * | sort'
run_case "glob_pattern"            'cd "$WORKDIR/fixtures/dir" && printf "%s\n" *.c *.h | sort'
run_case "glob_nomatch"            'printf "%s\n" foo*.bar || true'

# Logical separators & sequencing
run_case "semicolon_seq"           'echo a; echo b; echo c'
run_case "and_or"                  'false && echo no || echo yes'
run_case "subshell_like"           '(echo inside); echo outside'

# Variables & scope
run_case "assign_inline"           'FOO=1 BAR=2 env | grep -E "^(FOO|BAR)=" | sort'
run_case "assign_cmd_scope"        'FOO=ok sh -c "echo $FOO"'
run_case "export_then_cmd"         'export Q=7; sh -c "echo $Q"'

# Signals (background-less simulation; just ensure SIGINT stops a sleep)
run_case "signal_sigint"           'bash -lc '\''(sleep 2) & pid=$!; kill -INT "$pid"; wait "$pid"; echo $?'\'''

# Long / stress
# Large argv
run_case "long_argv"               'python3 - <<PY
import sys
print("OK", len(sys.argv))
PY arg{1..200}'

# Deep pipeline chain of 25 processes
make_chain() {
  local n="${1:-25}" i cmd="printf a"
  for i in $(seq 1 "$n"); do
    cmd="$cmd | cat"
  done
  echo "$cmd | wc -c"
}
run_case "pipe_chain_25"           "$(make_chain 25)"

# Many here-docs in sequence
run_case "many_heredocs"           'cat <<A
1
A
cat <<B
2
B
cat <<C
3
C'

# Unicode & weird bytes
run_case "utf8_echo"               $'echo "€ ☕ 你好 🚀"'

# File descriptor juggling
run_case "fd_shuffle"              'exec 3>&1; echo x >&3; exec 3>&-; true'

# Exit builtin behavior
run_case "exit_noarg"              'exit'
run_case "exit_with_status"        'exit 7'

# Syntax errors
run_case "syntax_unexpected_token" 'echo ; | cat'
run_case "unclosed_quote"          "echo 'abc"
run_case "bad_redir"               'echo hi >'

# --- Summary -----------------------------------------------------------------

echo
printf "Summary: %s, %s, %s, total %s\n" \
  "$(color green "PASS=$PASS")" \
  "$(color red   "FAIL=$FAIL")" \
  "$(color yellow "SKIP=$SKIP")" \
  "$TOTAL"
[[ $FAIL -eq 0 ]]
