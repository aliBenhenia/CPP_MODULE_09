#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <vector>
#include <deque>
#include <string>


class PmergeMe
{
    private:
        std::vector<int> numbers;
        int lastNumber;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        void start(std::string input);
        bool parseNumbers(std::string input);
        void SortPairs();
        void printNumbers();
        ~PmergeMe();
};


#endif