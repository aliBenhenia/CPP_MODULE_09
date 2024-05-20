#include "PmergeMe.hpp"

int main(int ac, char *av[])
{
    PmergeMe    p;

    if (ac < 2)
    {
        std::cout << "enter args..." << std::endl;
        return (1);
    }
    p.start_vector(ac, av);
    p.start_deque(ac, av);
    p.printTimeComplexity();
    return (0);
}
