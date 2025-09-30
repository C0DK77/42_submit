#!/bin/bash

echo "===== BONUS TEST 1: heredoc avec plusieurs redirections ====="
./minishell << EOF1 > tmp_output.txt << EOF2
ligne heredoc 1
EOF1
ligne heredoc 2
EOF2
cat tmp_output.txt
rm tmp_output.txt

echo -e "\n===== BONUS TEST 2: heredoc avec \$? ====="
./minishell << EOF
echo test
cat << END
Code retour précédent: $?
END
EOF

echo -e "\n===== BONUS TEST 3: heredoc vide ====="
./minishell << EOF
cat << END
END
EOF

echo -e "\n===== BONUS TEST 4: heredoc avec quotes + pipe ====="
./minishell << EOF
cat << 'DELIM' | grep mini
salut $USER
DELIM
EOF

echo -e "\n===== BONUS TEST 5: heredoc multiple avec expansion ====="
./minishell << EOF
export VAR1=42
export VAR2=hello
cat << END1
valeur: $VAR1
END1
cat << END2
mot: $VAR2
END2
EOF
