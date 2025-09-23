
#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

bool        ft_empty(const std::string& s);
int         ft_strlen(const std::string& s);
std::string ft_word(const std::string& s);
std::string ft_strreplace(const std::string& s, int pos, char c);
std::string ft_setw(const std::string& s, int width);
std::string int_to_string(int n);

#endif
