
#include "phonebook.hpp"
#include <iostream>
#include <string>

int main() 
{
    PhoneBook pb;
    std::string cmd;

    while (true) 
    {
        std::cout << "PLEASE ENTER A COMMANDE(ADD SEARCH or EXIT) : ";
        std::getline(std::cin, cmd);

        if (std::cin.eof())
            break;

        if (cmd == "ADD")
            pb.add();
        else if (cmd == "SEARCH")
            pb.search();
        else if (cmd == "EXIT")
            break;
        else
        {
            std::cout << "          !     UNKNOWN COMMANDE    !         " << std::endl;
            std::cout << "PLEASE ENTER A COMMANDE(ADD SEARCH or EXIT) : " << std::endl;
        }
    }
    return 0;
}
