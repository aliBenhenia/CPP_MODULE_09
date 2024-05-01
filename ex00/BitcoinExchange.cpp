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
    double          value;

    fileDb.open(db);
    if (fileDb.is_open() == 0)
        throw std::runtime_error("error : can't open a DB file");
    std::getline(fileDb, line); // ignore header
    while (std::getline(fileDb, line))
    {
        pos = line.find(',');
        if (pos != std::string::npos) // check is valid pos
        {
            std::string date_str, price_str;
            date_str = line.substr(0, pos);
            price_str = line.substr(pos + 1);
            std::istringstream iss(price_str);
            if (!(iss >> value))
            {
                std::cerr << "Error: failed to parse value for line => " << line << std::endl;
                continue;
            }
            btc_db[date_str] = value;
        }
    }
    fileDb.close();
}
void BitcoinExchange :: processInputFile(std::string db)
{
    std::ifstream   fileDb;
    std::string     line;
    std::string     date;
    size_t          pos;
    double          value;

    fileDb.open(db);
    if (fileDb.is_open() == 0)
        throw std::runtime_error("error : can't open a DB file");
    std::getline(fileDb, line); // ignore header
    if (line.empty())
        throw std::runtime_error("error : empty file");
    // check header 
    // date | value
// 2011-01-03 | 3
// 2011-01-03 | 2
// 2011-01-03 | 1
// 2011-01-03 | 1.2
// 2011-01-09 | 1
// 2012-01-11 | -1
// 2001-42-42
// 2012-01-11 | 1
// 2012-01-11 | 2147483648
    if (line.find('|') == std::string::npos)
        throw std::runtime_error("error : bad header");
    while (std::getline(fileDb, line))
    {
        pos = line.find('|');
        if (pos != std::string::npos) // check is valid pos
        {
            std::string date_str = line.substr(0, pos);
            std::string value_str = line.substr(pos + 1);
            std::istringstream iss(value_str);
            if (!(iss >> value))
            {
                std::cerr << "Error: failed to parse value for line => " << line << std::endl;
                continue;
            }
            if (value < 0)
            {
                std::cerr << "Error:not a positive number. " << std::endl;
                continue;
            }
            if (value > 1000)
            {
                std::cerr << "Error: too large a number"<< std::endl;
                continue;
            }
            std::map<std::string, double>::iterator it = btc_db.lower_bound(date_str);
            if (it == btc_db.end())
            {
                std::cerr << "Error: bad input =>" << line << std::endl;
                continue;
            }
            std::cout << date_str << " => " << value << " = " << it->second * value << std::endl;
            

        }
        else
            std::cerr << "Error: bad input =>" << line << std::endl;

    }
    fileDb.close();
}

BitcoinExchange::~BitcoinExchange()
{
    // std::cout << "destructor" << std::endl;
}