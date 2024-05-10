#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <utility>


class PmergeMe
{
    private:
        std::vector<int> numbers;
        std::vector<std::pair<int, int> > PairNumbers;
        std::vector<int> mainChain;
        std::vector<int> pendChain;

        std::vector<std::pair<int, int> > first;
        std::vector<std::pair<int, int> > second;
        std::vector<int> sorted;
        int lastNumber;


    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        void start(std::string input);
        bool parseNumbers(std::string input);
        void SortPairs();
        void splitPairs();
        void MergeSortPair(std::vector<std::pair<int, int> > &PairNumbers, size_t start, size_t end);
        void Merge(std::vector<std::pair<int, int> > &PairNumbers, size_t start, size_t mid, size_t end);
        void fillMainChainAndPend();
        void printNumbers();
        ~PmergeMe();
};


#endif