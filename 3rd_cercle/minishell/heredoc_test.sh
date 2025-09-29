#!/bin/bash

echo "===== TEST 1: heredoc simple ====="
./minishell << EOF
cat << END
bonjour
minishell
END
exit
EOF

echo -e "\n===== TEST 2: heredoc avec variable ====="
./minishell << EOF
export NAME=mini
cat << END
salut \$NAME
END
exit
EOF

echo -e "\n===== TEST 3: heredoc sans expansion (quotes) ====="
./minishell << EOF
export NAME=mini
cat << 'END'
salut \$NAME
END
exit
EOF

echo -e "\n===== TEST 4: heredoc non terminé (EOF) ====="
./minishell << EOF
cat << END
ligne sans fin
EOF

echo -e "\n===== TEST 5: heredoc avec pipe ====="
./minishell << EOF
cat << EOF | grep hello
hello minishell
bye
EOF
exit
EOF
