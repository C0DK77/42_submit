
#ifndef CONTACT_HPP
#define CONTACT_HPP

#include <string>

class Contact 
{

private:
    std::string first_name;
    std::string last_name;
    std::string nickname;
    std::string phone;
    std::string secret;

public:
    void set_contact();
    void print_contact();
    void print_summary(int index);
};

#endif
