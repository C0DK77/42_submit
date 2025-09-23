
#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "contact.hpp"

class PhoneBook {
private:
    Contact contacts[8];
    int count;
    int oldest;

public:
    PhoneBook();
    void add();
    void search();
};

#endif