
#include "Zombie.hpp"

Zombie* newZombie(std::string name);
void randomChump(std::string name);

int main() 
{
    std::cout << "\nCreating zombie on the heap:" << std::endl;
    Zombie* heapZombie = newZombie("HeapZombie");
    heapZombie->announce();
    delete heapZombie;

    std::cout << "\nCreating zombie on the stack:" << std::endl;
    randomChump("StackZombie");

    return 0;
}