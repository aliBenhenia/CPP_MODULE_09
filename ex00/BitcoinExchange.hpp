#ifndef BITCOINEXCHANGE
#define BITCOINEXCHANGE

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>// This header is part of the error handling library.

#define isMonth(x) (x >= 1 && x <= 12)
#define isYear(x) (x >= 2009 && x <= 2022)
#define isDay(x) (x >= 1 && x <= 31)
#define isMonthsWith31Days(x) (x == 1 || x == 3 || x == 5 || x == 7 || x == 8 || x == 10 || x == 12)
#define isMonthsWith30Days(x) (x == 4 || x == 6 || x == 9 || x == 11)

struct Date
{
    int day;
    int month;
    int year;
};

class BitcoinExchange
{
    private:
        std::map<std::string, double> btc_db;
    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange &obj);
        BitcoinExchange & operator =(BitcoinExchange &obj);
        // member fucntions
        void parseDataBase(std::string db);
        void processInputFile(std::string inputFile);
        double getClosestValue(std::string date);
        bool checkValidDate(std::string date);
        bool checkValidFormat(std::string line);
        bool checkValidValue(double value);
        void diplayResult(std::string date, double value);
        void print()
        {
           // std::cout << "print" << std::endl;
            for (std::map<std::string, double>::iterator it = btc_db.begin(); it != btc_db.end(); ++it)
                std::cout << "(" << it->first << ")"<< std::endl;
        }
        ~BitcoinExchange();
};

#endif