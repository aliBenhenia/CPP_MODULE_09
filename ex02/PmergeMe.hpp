#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <iostream>
#include <vector>
#include <deque>


class PmergeMe
{
    private:
        std::vector<int> numbers;
    public:
        PmergeMe();
        PmergeMe(const PmergeMe &other);
        PmergeMe &operator=(const PmergeMe &other);
        void start();
        ~PmergeMe();
};


#endif