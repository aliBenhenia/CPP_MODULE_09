#include "BitcoinExchange.hpp"

int main(int ac, char *av[])
{
    BitcoinExchange dt;
    if (ac != 2)
    {
        std::cout << "should pass input file" << std::endl;
        return (1);
        std::cout << av[0] << std::endl;
    }
    return 0;
}