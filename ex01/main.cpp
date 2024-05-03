#include "RPN.hpp"

int main(int ac, char *av[])
{
    RBN rbn;
    if (ac != 2)
    {
        std::cout << "should pass expression" << std::endl;
        return (1);
    }
    rbn.start(std::string(av[1]));
    return (0);
}