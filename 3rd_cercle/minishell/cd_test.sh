#!/bin/bash

echo "===== TEST 1: cd sans argument (HOME) ====="
./minishell << EOF
cd
pwd
exit
EOF

echo -e "\n===== TEST 2: cd vers /tmp ====="
./minishell << EOF
cd /tmp
pwd
exit
EOF

echo -e "\n===== TEST 3: cd - (OLDPWD) ====="
./minishell << EOF
cd /tmp
cd -
pwd
exit
EOF

echo -e "\n===== TEST 4: cd -- ====="
./minishell << EOF
cd --
pwd
exit
EOF

echo -e "\n===== TEST 5: PWD et OLDPWD tracking ====="
./minishell << EOF
pwd
cd /tmp
echo PWD = \$PWD
echo OLDPWD = \$OLDPWD
cd -
echo PWD = \$PWD
echo OLDPWD = \$OLDPWD
exit
EOF

echo "===== TEST 6: cd trop d'arguments ====="
./minishell << EOF
cd dir1 dir2
exit
EOF

echo -e "\n===== TEST 7: cd vers dossier inexistant ====="
./minishell << EOF
cd /this/does/not/exist
exit
EOF

echo -e "\n===== TEST 8: cd - sans OLDPWD ====="
./minishell << EOF
unset OLDPWD
cd -
exit
EOF

echo -e "\n===== TEST 9: cd -- avec argument ====="
./minishell << EOF
cd -- /tmp
exit
EOF

echo -e "\n===== TEST 10: cd -- sans HOME ====="
./minishell << EOF
unset HOME
cd --
exit
EOF

echo -e "\n===== TEST 6: cd avec option invalide ====="
./minishell << EOF
cd -invalid
exit
EOF
