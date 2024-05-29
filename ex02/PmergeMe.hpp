#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <vector>
#include <deque>
#include <string>
#include <utility>
#include <ctime>


class PmergeMe
{
    private: 
        std::vector<int> numbers;
        std::vector<std::pair<int, int> > PairNumbers;
        std::vector<int> mainChain;
        std::vector<int> pendChain;
        std::vector<int> combination;

        std::vector<std::pair<int, int> > first;
        std::vector<std::pair<int, int> > second;
        std::vector<int> sorted;
        int lastNumber;
        std::clock_t start1;
        std::clock_t end1;

    private: 
        std::deque<int> numbersDeque;
        std::deque<std::pair<int, int> > PairNumbersDeque;
        std::deque<int> mainChainDeque;
        std::deque<int> pendChainDeque;
        std::deque<int> combinationDeque;

        std::deque<std::pair<int, int> > firstDeque;
        std::deque<std::pair<int, int> > secondDeque;
        std::deque<int> sortedDeque;
        int lastNumberDeque;
        std::clock_t start2;
        std::clock_t end2;

    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        void start_vector(int ac, char *av[]);
        bool parseNumbers(int ac, char *av[]);
        bool processNumber(std::string input);
        void SortPairs();
        void splitPairs();
        void MergeSortPair(std::vector<std::pair<int, int> > &PairNumbers, size_t start, size_t end);
        void Merge(std::vector<std::pair<int, int> > &PairNumbers, size_t start, size_t mid, size_t end);
        void fillMainChainAndPend();
        void sortingResult();
        void createComb();
        std::vector<int> genertaingJacobSequence();
        void printNumbers();
        size_t getMiddle(size_t start, size_t end);
        bool    isOdd(size_t numberSize);
        bool    isEven(size_t index);
        void printBeforeSort();
        
        void start_deque(int ac, char *av[]);
        bool parseNumbersDeque(int ac, char *av[]);
        bool processNumberDeque(std::string input);
        void SortPairsDeque();
        void splitPairsDeque();
        void MergeSortPairDeque(std::deque<std::pair<int, int> > &PairNumbers, size_t start, size_t end);
        void MergeDeque(std::deque<std::pair<int, int> > &PairNumbers, size_t start, size_t mid, size_t end);
        void fillMainChainAndPendDeque();
        void sortingResultDeque();
        void createCombDeque();
        std::deque<int> genertaingJacobSequenceDeque();
        void printNumbersDeque();
        size_t getMiddleDeque(size_t start, size_t end);
        bool    isOddDeque(size_t numberSize);
        bool    isEvenDeque(size_t index);
        void printBeforeSortDeque();
        void printTimeComplexity();
        ~PmergeMe();
};

#endif