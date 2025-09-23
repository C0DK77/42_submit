
#include <iostream>
#include <string>

int ft_strlen(std::string& s)
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
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return 0;
	}

	for (int i = 1; i < argc; i++) 
	{
		std::string s = argv[i];
		for (int j = 0; j < ft_strlen(s); j++) 
		{
			if (ft_islower(s[j]))
				std::cout << (char)(s[j] - 32);
			else
				std::cout << s[j];
		}
	}
	std::cout << std::endl;
	return 0;
}
