#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange()
{
    // std::cout << "default constructor" << std::endl;
}

BitcoinExchange::BitcoinExchange(BitcoinExchange &obj)
{
    this->btc_db = obj.btc_db;
    // std::cout << "copy constructor" << std::endl;
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
    std::ifstream   fileDb;
    std::string     line;
    std::string     date;
    size_t          pos;

    fileDb.open(db);
    if (fileDb.is_open() == 0)
        throw std::runtime_error("error : can't open a DB file");
    std::getline(fileDb, line); // ignore header
    while (std::getline(fileDb, line))
    {
        pos = line.find(',');
        if (pos != std::string::npos) // check is valid pos
        {
            std::stringstream ss(line);
            std::string date_str, price_str;
            if (std::getline(ss, date_str, ',') && getline(ss, price_str, ','))
            {
                char* endPtr;
                double price = std::strtod(price_str.c_str(), &endPtr);
                if (endPtr == NULL)
                     throw std::runtime_error("error : fail conversion");
                this->btc_db[date_str] = price;
            }
        }
    }
    fileDb.close();
}
void BitcoinExchange :: processInputFile(std::string db)
{
    (void)db;
}

BitcoinExchange::~BitcoinExchange()
{
    // std::cout << "destructor" << std::endl;
}