
#include "phonebook.hpp"
#include "../utils/utils.hpp" 
#include <iostream>

PhoneBook::PhoneBook() : count(0), oldest(0) {}

void PhoneBook::add() 
{
    if (count < 8) 
	{
        contacts[count].set_contact();
        count++;
    } 
	else 
	{
        contacts[oldest].set_contact();
        oldest = (oldest + 1) % 8;
    }
}

void PhoneBook::search() 
{
    if (count == 0) {
        std::cout << "No contacts registred" << std::endl;
        return;
    }

    std::cout << ft_setw("Index", 10) << "|"
              << ft_setw("First Name", 10) << "|"
              << ft_setw("Last Name", 10) << "|"
              << ft_setw("Nickname", 10) << std::endl;

    for (int i = 0; i < count; ++i)
        contacts[i].print_summary(i + 1);

    std::cout << "Entrez l'index du contact à afficher : ";
    std::string input;
    std::getline(std::cin, input);

    if (input.size() != 1 || !isdigit(input[0])) 
	{
        std::cout << "Index invalide." << std::endl;
        return;
    }

    int index = input[0] - '0';
    if (index < 1 || index > count) 
	{
        std::cout << "Index hors limites." << std::endl;
        return;
    }

    contacts[index - 1].print_contact();
}
