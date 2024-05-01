#ifndef BITCOINEXCHANGE
#define BITCOINEXCHANGE

#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <stdexcept>// This header is part of the error handling library.

class BitcoinExchange
{
    private:
        std::map<std::string, float> btc_db;
        std::vector<std::string> sd;
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