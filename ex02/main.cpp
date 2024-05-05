#include "PmergeMe.hpp"


int main(int ac, char *av[])
{
    PmergeMe p;
    if (ac != 2)
    {
        std::cout << "usage: ./PmergeMe [input]" << std::endl;
        return (1);
    }
    p.start(av[1]);
    p.printNumbers();
    return (0);
}