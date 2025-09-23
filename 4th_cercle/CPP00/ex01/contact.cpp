
#include "contact.hpp"
#include "utils.hpp" 
#include <iostream>
#include <sstream>

void Contact::set_contact() 
{
    do 
    {
        std::cout << "First name :";
        getline(std::cin, first_name);
    } 
    while (ft_empty(first_name));
    do 
    {
        std::cout << "Last name :";
        getline(std::cin, last_name);
    } 
    while (ft_empty(last_name));
    do 
    {
        std::cout << "Nickname :";
        getline(std::cin, nickname);
    } 
    while (ft_empty(nickname));
    do 
    {
        std::cout << "Phone :";
        getline(std::cin, phone);
    } 
    while (ft_empty(phone));
    do 
    {
        std::cout << "Darkest secret :";
        getline(std::cin, secret);
    } 
    while (ft_empty(secret));
}

void Contact::print_summary(int i) 
{
    std::string a = int_to_string(i);
    std::cout << ft_setw(a, 10) << "|"
              << ft_setw(ft_word(first_name), 10) << "|"
              << ft_setw(ft_word(last_name), 10)  << "|"
              << ft_setw(ft_word(nickname), 10) << std::endl;
}

void Contact::print_contact() 
{
    std::cout << "First name: " << first_name << std::endl;
    std::cout << "Last name: " << last_name << std::endl;
    std::cout << "Nickname: " << nickname << std::endl;
    std::cout << "Phone number: " << phone << std::endl;
    std::cout << "Darkest secret: " << secret << std::endl;
}
