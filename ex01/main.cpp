#include "RPN.hpp"

int main(int ac, char *av[])
{
    RBN rbn;
    if (ac != 2)
    {
        std::cout << "should pass expression" << std::endl;
        return (1);
    }
    try
    {
        rbn.start(std::string(av[1]));
    }
    catch(const char *e)
    {
        std::cout << e << std::endl;
    }
    return (0);
}