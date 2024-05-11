#include "PmergeMe.hpp"


int main(int ac, char *av[])
{
    PmergeMe    p;

    if (ac < 2)
    {
        std::cout << "enter args..." << std::endl;
        return (1);
    }
    p.start(ac, av);
    p.printNumbers();
    return (0);
}
