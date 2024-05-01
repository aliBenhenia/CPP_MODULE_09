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
    Date            date; // construct data with -1 
    double          value;
    std::string     dateString;
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
            dateString = line.substr(0, pos);
            line.erase(0, pos + 1);
            pos = dateString.find('-');
            if (pos != std::string::npos)
            {
                date.year = std::atoi(dateString.substr(0, pos).c_str());
                dateString.erase(0, pos + 1);
                pos = dateString.find('-');
                if (pos != std::string::npos)
                {
                    date.month = std::atoi(dateString.substr(0 , pos).c_str());
                    dateString.erase(0, pos + 1);
                    date.day = std::atoi(dateString.substr(0 , pos).c_str());
                    value = std::atof(line.c_str());
                    this->btc_db[date] = value;
                }
            }
        }

    }
    // at end close it
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