#!/bin/bash

LEVEL=0
MAX=10 # 🧠 Ne pas mettre 50 au début pour ne pas surcharger valgrind
MINISHELL=./minishell

echo "🧠 [VALGRIND MODE] Lancement de $MAX minishells récursives..."

while [ $LEVEL -lt $MAX ]; do
	echo ""
	echo "🔁 [LEVEL $LEVEL] valgrind --leak-check=full $MINISHELL"
	valgrind --leak-check=full --error-exitcode=42 --quiet $MINISHELL << EOF
$MINISHELL
exit
EOF

	EXIT_CODE=$?

	if [ $EXIT_CODE -eq 42 ]; then
		echo "💥 Valgrind a détecté une fuite mémoire à la profondeur $LEVEL"
		break
	elif [ $EXIT_CODE -ne 0 ]; then
		echo "💥 minishell a crashé ou échoué (exit code = $EXIT_CODE)"
		break
	fi

	LEVEL=$((LEVEL + 1))
done

echo ""
echo "✅ Test terminé à la profondeur $LEVEL"
