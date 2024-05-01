#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    std::cout << "default constructor" << std::endl;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange &obj)
{
    this->btc_db = obj.btc_db;
    std::cout << "copy constructor" << std::endl;
}

BitcoinExchange &BitcoinExchange::operator=(BitcoinExchange &obj)
{
    this->btc_db = obj.btc_db;
    std::cout << "copy assignement" << std::endl;
    return (*this);
}
// member functions
void BitcoinExchange :: parseDataBase(std::string db)
{
    
}
void BitcoinExchange :: processInputFile(std::string db)
{
    
}

BitcoinExchange::~BitcoinExchange()
{
    std::cout << "destructor" << std::endl;
}