#!/bin/bash

echo "===== TEST 1: unset d'une variable existante ====="
./minishell << EOF
export VAR1=hello
unset VAR1
env
exit
EOF

echo -e "\n===== TEST 2: unset d'une variable inexistante ====="
./minishell << EOF
unset UNKNOWN_VAR
env
exit
EOF

echo -e "\n===== TEST 3: unset avec identifiant invalide (123abc) ====="
./minishell << EOF
unset 123abc
exit
EOF

echo -e "\n===== TEST 4: unset avec = dans l'identifiant ====="
./minishell << EOF
unset FOO=BAR
exit
EOF

echo -e "\n===== TEST 5: unset avec option invalide ====="
./minishell << EOF
unset -f
exit
EOF

echo -e "\n===== TEST 6: unset multiple variables ====="
./minishell << EOF
export A=1 B=2 C=3
unset A B
env
exit
EOF
