#include "BitcoinExchange.hpp"

int main(int ac, char *av[])
{
    BitcoinExchange exchange;
    try
    {
        if (ac != 2)
            throw std::invalid_argument("should pass input file");
        exchange.parseDataBase("data.csv");
        exchange.processInputFile(av[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}