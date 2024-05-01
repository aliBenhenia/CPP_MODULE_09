#ifndef BITCOINEXCHANGE
#define BITCOINEXCHANGE

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <stdexcept>// This header is part of the error handling library.

struct Date {
    int year;
    int month;
    int day;
    Date()
    {
        this->year  = -1;
        this->month = -1;
        this->day   = -1;
    }
    Date(int yr, int mt, int dy)
    {
        this->year  = yr;
        this->month = mt;
        this->day   = dy;
    }
    bool operator<(Date& other) const 
    {
        if (year != other.year) return year < other.year;
        if (month != other.month) return month < other.month;
        return day < other.day;
    }
};

class BitcoinExchange
{
    private:
        std::map<Date, double> btc_db;
    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange &obj);
        BitcoinExchange & operator =(BitcoinExchange &obj);
        // member fucntions
        void parseDataBase(std::string db);
        void processInputFile(std::string inputFile);
        ~BitcoinExchange();
       
};
#endif