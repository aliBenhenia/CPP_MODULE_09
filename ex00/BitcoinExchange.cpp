#include "BitcoinExchange.hpp"
std::string trimSpaces(std::string str)
{
    size_t start = str.find_first_not_of(" ");
    size_t end = str.find_last_not_of(" ");
    return str.substr(start, end - start + 1);
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
                std::cout << "Error: failed to parse value for line => " << line << std::endl;
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
bool isValidDateFormat(std::string date)
{
   // tream spaces from the beginning
    if (date.length() != 10)
        return (false);
    if (date[4] != '-' || date[7] != '-')
        return (false);
    return (true);
}

Date parseDateStr(std::string date)
{
    Date dateObj;
    std::string year = date.substr(0, 4);
    std::string month = date.substr(5, 2);
    std::string day = date.substr(8, 2);
    dateObj.year = std::atoi(year.c_str());
    dateObj.month = std::atoi(month.c_str());
    dateObj.day = std::atoi(day.c_str());
    return (dateObj);
}

bool BitcoinExchange::checkValidDate(std::string date)
{
    date = trimSpaces(date);
    if(isValidDateFormat(date) == (false))
        return (false);
    Date dateObj = parseDateStr(date);
    if (isYear(dateObj.year) == (false) || isMonth(dateObj.month) == (false))
        return (false);
    // leap year
    if (dateObj.year % 4 == 0 && dateObj.month == 2) // month is feb == 2
    {
        if (dateObj.day < 1 || dateObj.day > 29)
            return (false);
    }
    else if (dateObj.month == 2)
    {
        if (dateObj.day < 1 || dateObj.day > 28)
            return (false); // ivnalid day for month in non leap year
    }
    if (isMonthsWith31Days(dateObj.month) == (true))
    {
        if (dateObj.day < 1 || dateObj.day > 31)
            return (false);
    }
    else if (isMonthsWith30Days(dateObj.month) == (true))
    {
        if (dateObj.day < 1 || dateObj.day > 30)
            return (false);
    }
    return (true);
}
bool BitcoinExchange::checkValidFormat(std::string line)
{
    size_t pos = line.find('|');
    if (pos == std::string::npos)// if invalid pos
        return (false);
    if (pos == 0 || pos == line.length() - 1) // if pos is at the beginning or end
        return (false);
    return (true);
}

bool BitcoinExchange::checkValidValue(double value)
{
    if (value < 0)
    {
        std::cout << "Error: not a positive number"  << std::endl;
        return (false);
    }
    if (value > 1000)
    {
        std::cout << "Error: too large a number"  << std::endl;
        return (false);
    }
    return (true);
}

void BitcoinExchange::diplayResult(std::string date, double value)
{
    date = trimSpaces(date);
    double closestValue = getClosestValue(date);
    double result = value * closestValue;
    std::cout << date << " => " << value << " = "  << result << std::endl;
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
        if (checkValidFormat(line) == (false))
        {
            std::cout << "Error: bad input =>" << line << std::endl;
            continue;
        }
        if (checkValidDate(line.substr(0, pos)) == (false))
        {
            std::cout << "Error: bad date =>" << line << std::endl;
            continue;
        }
        std::string value_str = line.substr(pos + 1);
        std::istringstream iss(value_str);
        if (!(iss >> value))
        {
            std::cout << "Error: failed to parse value for line => " << line << std::endl;
            continue;
        }
        if (checkValidValue(value) == (false))
            continue;
       diplayResult(line.substr(0, pos), value);
    }
    fileDb.close();
}

BitcoinExchange::~BitcoinExchange()
{
    // std::cout << "destructor" << std::endl;
}