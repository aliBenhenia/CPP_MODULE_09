#include "BitcoinExchange.hpp"
std::string trimDate(const std::string& str, const std::string& chars = " \t\n\r") {
   // rm  spaces from the beginning
    size_t start = str.find_first_not_of(chars);
    if (start == std::string::npos)
        return "";
    return str.substr(start, str.find_last_not_of(chars) - start + 1);
}

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

double BitcoinExchange :: getClosestValue(std::string date)
{
    std::map<std::string, double>::iterator it = btc_db.begin();
    double closestValue = it->second;
    for (std::map<std::string, double>::iterator it = btc_db.begin(); it != btc_db.end(); ++it)
    {
        if (it->first > date)
            break;
        closestValue = it->second;
    }
    return closestValue;
}

bool BitcoinExchange::checkValidDate(std::string date)
{
    // should trim date string by removing spaces from the beginning and the end
    // date = trimDate(date);
    // date += " ";    
    // std::cout << "(" << date << ")" << std::endl;
    // hndle leap year and month
    // leap year
    if (date[5] == '0' && date[6] == '2' && date[8] == '2' && date[9] == '9')
    {
        if (date[0] != '2' || date[1] != '0')
            return false;
        if (date[2] != '0' || date[3] != '4')
            return false;
        return true;
    }
    if (date[4] != '-' || date[7] != '-')
        return false;
    for (int i = 0; i < 10; i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (date[i] < '0' || date[i] > '9')
            return false;
    }
    return true;
}
bool BitcoinExchange::checkValidFormat(std::string line)
{
    size_t pos = line.find('|');
    if (pos == std::string::npos)
        return false;
    if (pos == 0 || pos == line.length() - 1)
        return false;
    return true;
}
bool BitcoinExchange::checkValidValue(double value)
{
    if (value < 0)
    {
        std::cerr << "Error: not a positive number"  << std::endl;
        return false;
    }
    if (value > 1000)
    {
        std::cerr << "Error: too large a number"  << std::endl;
        return false;
    }
    return true;
}

void BitcoinExchange::diplayResult(std::string date, double value)
{
    double closestValue = getClosestValue(date);
    double result = value * closestValue;
    std::cout << date << " | " << value << " | " << closestValue << " | " << result << std::endl;
}

void BitcoinExchange :: processInputFile(std::string db)
{
    std::ifstream   fileDb;
    std::string     line;
    size_t          pos;
    double          value;

    fileDb.open(db);
    if (fileDb.is_open() == 0)
        throw std::runtime_error("error : can't open a DB file");
    std::getline(fileDb, line); // ignore header
    if (line.empty())
        throw std::runtime_error("error : empty file");
    if (line != "date | value")
        throw std::runtime_error("error : bad header");
    while (std::getline(fileDb, line))
    {
        pos = line.find('|');
        if (checkValidFormat(line) == false)
        {
            std::cerr << "Error: bad input =>" << line << std::endl;
            continue;
        }
        if (checkValidDate(line.substr(0, pos)) == false)
        {
            std::cerr << "Error: bad date =>" << line << std::endl;
            continue;
        }
        std::string value_str = line.substr(pos + 1);
        std::istringstream iss(value_str);
        if (!(iss >> value))
        {
            std::cerr << "Error: failed to parse value for line => " << line << std::endl;
            continue;
        }
        if (checkValidValue(value) == false)
            continue;
       diplayResult(line.substr(0, pos), value);
    }
    fileDb.close();
}

BitcoinExchange::~BitcoinExchange()
{
    // std::cout << "destructor" << std::endl;
}