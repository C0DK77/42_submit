#!/bin/bash

echo "===== TEST 1: export d'une variable ====="
./minishell << EOF
export FOO=bar
env
exit
EOF

echo -e "\n===== TEST 2: export sans valeur ====="
./minishell << EOF
export TEST
env
exit
EOF

echo -e "\n===== TEST 3: unset d'une variable ====="
./minishell << EOF
export TEMP=42
unset TEMP
env
exit
EOF

echo -e "\n===== TEST 4: export identifiant invalide ====="
./minishell << EOF
export =INVALID
exit
EOF

echo -e "\n===== TEST 5: unset identifiant invalide ====="
./minishell << EOF
unset 123abc
exit
EOF

echo -e "\n===== TEST 6: export avec +=' (append) ====="
./minishell << EOF
export LANG=fr
export LANG+=-FR
env
exit
EOF
