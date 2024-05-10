#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{}

PmergeMe::PmergeMe(const PmergeMe &other)
{
    *this = other;
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    numbers = other.numbers;
    return *this;
}

bool PmergeMe::processNumber(std::string input)
{
    std::string number;
    size_t i = 0;

    if (input.size() == 0)
        return (false);
    if (input[0] == '-')
        return (false);
    if (input[0] == '+')
        i++;
    while (i < input.size())
    {
        if (std::isdigit(input[i]))
            number += input[i];
        else
            return (false);
        i++;
    }
    if (number.size() > 0)
        numbers.push_back(std::atoi(number.c_str()));
    if (numbers.size() == 0)
        return (false);
    return (true);
}

bool PmergeMe::parseNumbers(int ac , char *av[])
{
    int i = 1;
    while (i < ac)
    {
        if (processNumber(av[i]) == false)
            return (false);
        i++;
    }
    return (true);
}

// alg Ford-Johnson algorithm merge-insert sort algorithm
void PmergeMe::SortPairs()
{
    size_t i = 0;
    if (numbers.size() % 2 != 0)
    {
        this->lastNumber = numbers.back();
        numbers.pop_back();
    }
    else
        this->lastNumber = -1;
    while (i < numbers.size() - 1)
    {
        // if (i % 2 == 0 && numbers[i] < numbers[i + 1])// for the first element of pair
        //     std::swap(numbers[i], numbers[i + 1]);
        if (numbers[i] < numbers[i + 1])
            std::swap(numbers[i], numbers[i + 1]);
        i += 2;
    }
}

void PmergeMe::splitPairs()
{
    size_t i = 0;

    while (i < numbers.size() -1)// -1 for the last element of pair
    {
        if (i % 2 == 0)// for the first element of pair
            PairNumbers.push_back(std::make_pair(numbers[i], numbers[i + 1]));
        i++;
    }
}

void PmergeMe::Merge(std::vector<std::pair<int, int> > &PairNumbers, size_t start, size_t mid, size_t end)
{
    (void)PairNumbers;
    (void)start;
    (void)mid;
    (void)end;

    if (start == end && mid == end) // if the array has only one element
        return;
    size_t lenArr1 = mid - start + 1;
    size_t lenArr2 = end - mid;
    size_t i = 0;
    std::vector<std::pair<int, int> > leftArr(lenArr1);
    std::vector<std::pair<int, int> > rightArr(lenArr2);

    // copy the left part of array
    while (i < lenArr1)
    {
        leftArr[i] = PairNumbers[start + i];
        i++;
    }
    i = 0;
    while (i < lenArr2)
    {
        rightArr[i] = PairNumbers[mid + 1 + i];
        i++;
    }
    size_t idxArr1 = 0;
    size_t idxArr2 = 0;

    size_t idxMerged = start;
    while (idxArr1 < lenArr1 && idxArr2 < lenArr2)
    {
        if (leftArr[idxArr1].first <= rightArr[idxArr2].first)
        {
            PairNumbers[idxMerged] = leftArr[idxArr1];
            idxArr1++;
        }
        else
        {
            PairNumbers[idxMerged] = rightArr[idxArr2];
            idxArr2++;
        }
        idxMerged++;
    }
    while (idxArr1 < lenArr1)
    {
        PairNumbers[idxMerged] = leftArr[idxArr1];
        idxArr1++;
        idxMerged++;
    }
    while (idxArr2 < lenArr2)
    {
        PairNumbers[idxMerged] = rightArr[idxArr2];
        idxArr2++;
        idxMerged++;
    }


}

void PmergeMe::MergeSortPair(std::vector<std::pair<int, int> > &PairNumbers, size_t start, size_t end)
{
    int mid;

    if (start >= end) // if the array has only one element
        return;
    mid = start + (end  - start) / 2; // for divide the array into two parts
    MergeSortPair(PairNumbers, start, mid); // for left part of array .. recursive call .. divide and conquer
    MergeSortPair(PairNumbers, mid + 1, end); // for right part of array .. recursive call .. divide and conquer
    Merge(PairNumbers, start, mid, end); // merge the two parts of array .. conquer .. merge  the two parts of array 
}
void PmergeMe::fillMainChainAndPend()
{
   std::vector<std::pair<int, int> >:: iterator it;

    for (it = PairNumbers.begin(); it != PairNumbers.end(); it++)
    {
        if (it == PairNumbers.begin())
        {
            mainChain.push_back(it->first);
            mainChain.push_back(it->second);
            pendChain.push_back(it->second);
            continue;
        }
        mainChain.push_back(it->first);
        pendChain.push_back(it->second);
    }



}

void PmergeMe::printNumbers()
{
    
   std::vector<std::pair<int, int> >::iterator it;

    for (it = PairNumbers.begin(); it != PairNumbers.end(); it++)
        std::cout << "[" << it->first  << " " << it->second << "]" << std::endl;
}

void PmergeMe::start(int ac, char *av[])
{
    if (parseNumbers(ac, av) == false)
    {
        std::cout << "invalid input ...plz enter correct input" << std::endl;
        numbers.clear();
        return;
    }
    SortPairs();
    splitPairs();
    MergeSortPair(this->PairNumbers, 0, this->PairNumbers.size() - 1);
    // fillMainChainAndPend();
}


PmergeMe::~PmergeMe()
{
}
