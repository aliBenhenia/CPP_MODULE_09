#ifndef BITCOINEXCHANGE
#define BITCOINEXCHANGE

#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <sstream>
#include <stdexcept>// This header is part of the error handling library.


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
        void print()
        {
           // std::cout << "print" << std::endl;
            for (std::map<std::string, double>::iterator it = btc_db.begin(); it != btc_db.end(); ++it)
                std::cout << it->first << " => " << it->second << std::endl;
        }
        ~BitcoinExchange();
       
};
#endif