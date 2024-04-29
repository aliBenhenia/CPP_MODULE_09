#ifndef BITCOINEXCHANGE
#define BITCOINEXCHANGE

#include <iostream>
#include <map>
#include <string>
#include <vector>



class BitcoinExchange
{
    private:
        std::map<std::string, float> btc_db;
        std::vector<std::string> sd;
    public:
        BitcoinExchange();
        BitcoinExchange(BitcoinExchange &obj);
        BitcoinExchange & operator =(BitcoinExchange &obj);
        ~BitcoinExchange();
       
};
#endif