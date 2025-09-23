
#include <iostream>
#include <sstream>

int ft_strlen(const std::string& s)
{
	int i = 0;
	while (s[i] != '\0')
		i++;
	return i;
}

std::string ft_strreplace (const std::string& s, int pos, char c) 
{
	std::string res;
	for (int i = 0; i < pos && i < ft_strlen(s); i++)
		res += s[i];
	return res += c;
}

bool ft_empty (const std::string& s) 
{
    return s[0] == '\0';
}

std::string ft_word (const std::string& s) 
{
    if (ft_strlen(s) > 10)
        return ft_strreplace(s, 9, '.');
    return s;
}

std::string ft_setw(const std::string& s, int i) {
    if (ft_strlen(s) >= i)
        return s;
    return std::string(i - ft_strlen(s), ' ') + s;
}

std::string int_to_string(int n) 
{
    std::stringstream ss;
    ss << n;
    return ss.str();
}
