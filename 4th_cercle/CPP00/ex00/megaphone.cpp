// $>./megaphone "shhhhh... I think the students are asleep..."
// SHHHHH... I THINK THE STUDENTS ARE ASLEEP...
// $>./megaphone Damnit " ! " "Sorry students, I thought this thing was off."
// DAMNIT ! SORRY STUDENTS, I THOUGHT THIS THING WAS OFF.
// $>./megaphone
// * LOUD AND UNBEARABLE FEEDBACK NOISE *

#include <iostream>
#include <string>

using namespace	std;

int ft_strlen(string& s)
{
	int i = 0;
	while (s[i] != '\0')
		i++;
	return i;
}

bool ft_isupper(char c)
{
	return (c >= 65 && c <= 90);
}

bool ft_islower(char c)
{
	return (c >= 97 && c <= 122);
}

int	main(int argc, char **argv)
{
	if (argc == 1) {
		cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << endl;
		return 0;
	}

	for (int i = 1; i < argc; i++) {
		string s = argv[i];
		for (int j = 0; j < ft_strlen(s); j++) {
			if (ft_islower(s[j]))
				cout << (char)(s[j] - 32);
			else
				cout << s[j];
		}
	}
	cout << endl;
	return 0;
}
