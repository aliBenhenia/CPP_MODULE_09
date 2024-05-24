#include "PmergeMe.hpp"

int main(int ac, char *av[])
{
    PmergeMe    p;

    if (ac < 2)
    {
        std::cout << "enter args..." << std::endl;
        return (1);
    }
    try
    {
        p.start_vector(ac, av);
        p.start_deque(ac, av);
        p.printTimeComplexity();
    }
    catch(const char *e)
    {
        std::cerr << e << '\n';
        return (1);
    }
    return (0);
}
