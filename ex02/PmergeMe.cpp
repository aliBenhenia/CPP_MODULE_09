#include "PmergeMe.hpp"

PmergeMe::PmergeMe()
{
}

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
    {
        int num = std::atoi(number.c_str());
        if (num < 0)
            return (false);
        numbers.push_back(num);
    }
    if (numbers.size() == 0)
        return (false);
    return (true);
}

bool PmergeMe::parseNumbers(int ac, char *av[])
{
    int i = 1;
    if (ac == 2)
        return(false);
    while (i < ac)
    {
        if (processNumber(av[i]) == false)
            return (false);
        i++;
    }
    return (true);
}

bool PmergeMe::isOdd(size_t numberSize)
{
    if (numberSize % 2 != 0)
        return (true);
    return (false);
}

// alg Ford-Johnson algorithm merge-insert sort algorithm
void PmergeMe::SortPairs()
{
    size_t i = 0;
    if (isOdd(numbers.size()))// if the number of elements is odd mean the last element is not in pair
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
        if (numbers[i] < numbers[i + 1]) // for the first element of pair mean the first element is less than the second element
            std::swap(numbers[i], numbers[i + 1]); // swap the two elements
        i += 2;
    }
}

void PmergeMe::splitPairs()
{
    size_t i = 0;
    if (isOdd(numbers.size()))// if the number of elements is odd mean the last element is not in pair
    {
        this->lastNumber = numbers.back();
        numbers.pop_back();
    }
    else
        this->lastNumber = -1;
    while (i < numbers.size() - 1) // -1 for the last element of pair
    {
        if (i % 2 == 0) // for the first element of pair
            PairNumbers.push_back(std::make_pair(numbers[i], numbers[i + 1]));
        i++;
    }
    i = 0;
    // sort the pair numbers
    while (i < PairNumbers.size())
    {
        if (PairNumbers[i].first < PairNumbers[i].second) // for the first element of pair mean the first element is greater than the second element
            std::swap(PairNumbers[i].first, PairNumbers[i].second); // swap the two elements
        i++;
    }
}

void PmergeMe::Merge(std::vector<std::pair<int, int> > &PairNumbers, size_t start, size_t mid, size_t end)
{
    if (start == end && mid == end) // if the array has only one element
        return;
    size_t lenArr1 = mid - start + 1;
    size_t lenArr2 = end - mid;
    size_t i = 0;
    std::vector<std::pair<int, int> > leftArr(lenArr1);
    std::vector<std::pair<int, int> > rightArr(lenArr2);

    // copy the left part of array
    while (i < lenArr1) // copy the left part of array
    {
        leftArr[i] = PairNumbers[start + i];
        i++;
    }
    i = 0;
    while (i < lenArr2) // copy the right part of array
    {
        rightArr[i] = PairNumbers[mid + 1 + i];
        i++;
    }
    size_t idxArr1 = 0;
    size_t idxArr2 = 0;

    size_t idxMerged = start;                      // for the merged array strating from the start index
    while (idxArr1 < lenArr1 && idxArr2 < lenArr2) // merge the two parts of array
    {
        if (leftArr[idxArr1].first <= rightArr[idxArr2].first) // compare the first element of pair
        {
            PairNumbers[idxMerged] = leftArr[idxArr1]; // copy the left part of array
            idxArr1++;                                 // increment the index of left part of array
        }
        else
        {
            PairNumbers[idxMerged] = rightArr[idxArr2]; // copy the right part of array
            idxArr2++;                                  // increment the index of right part of array
        }
        idxMerged++; // increment the index of merged array
    }
    while (idxArr1 < lenArr1) // if there are remaining elements in the left part of array
    {
        PairNumbers[idxMerged] = leftArr[idxArr1]; // copy the remaining elements of left part of array
        idxArr1++;                                 // increment the index of left part of array
        idxMerged++;                               // increment the index of merged array
    }
    while (idxArr2 < lenArr2) // if there are remaining elements in the right part of array
    {
        PairNumbers[idxMerged] = rightArr[idxArr2]; // copy the remaining elements of right part of array
        idxArr2++;                                  // increment the index of right part of array
        idxMerged++;                                // increment the index of merged array
    }
}

size_t PmergeMe::getMiddle(size_t start, size_t end)
{
    return (start + (end - start) / 2);
}
void PmergeMe::MergeSortPair(std::vector<std::pair<int, int> > &PairNumbers, size_t start, size_t end)
{
    size_t mid;

    if (start >= end) // if the array has only one element
        return;
    mid = getMiddle(start, end);          // for divide the array into two parts
    MergeSortPair(PairNumbers, start, mid);   // for left part of array .. recursive call .. divide and conquer
    MergeSortPair(PairNumbers, mid + 1, end); // for right part of array .. recursive call .. divide and conquer
    Merge(PairNumbers, start, mid, end);      // merge the two parts of array .. conquer .. merge  the two parts of array
}
void PmergeMe::fillMainChainAndPend()
{
    bool isFirstIteration = true;
    std::vector<std::pair<int, int> >::iterator it;

    for (it = PairNumbers.begin(); it != PairNumbers.end(); it++)
    {
        if (isFirstIteration)
        {
            mainChain.push_back(it->second);
            mainChain.push_back(it->first);
            pendChain.push_back(it->second);
            isFirstIteration = false;
            continue;
        }
        mainChain.push_back(it->first);
        pendChain.push_back(it->second);
    }
}

void PmergeMe::printNumbers()
{
    // print main chain and pend chain
    std::vector<int>::iterator it;
    std::vector<int>::iterator it2;
    std::cout << "\n main chain: ";
    for (it = mainChain.begin(); it != mainChain.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

std::vector<int> PmergeMe::genertaingJacobSequence()
{
    size_t i = 2;

    std::vector<int> jacobNumbers;
    jacobNumbers.push_back(0);
    jacobNumbers.push_back(1);

    while (i < 20)
    {
        jacobNumbers.push_back(jacobNumbers[i - 1] + (2 * jacobNumbers[i - 2]));
        i++;
    }
    jacobNumbers.erase(jacobNumbers.begin() + 1);
    return (jacobNumbers);
}

void PmergeMe::createComb()
{
    std::vector<int> jacobNumbers = genertaingJacobSequence();

    combination.push_back(0);

    int i = 1;
    while (i < 20)
    {
        combination.push_back(jacobNumbers[i]);
        int j = jacobNumbers[i - 1] + 1;
        while (j < jacobNumbers[i])
        {
            combination.push_back(j);
            j++;
        }
        if (combination.size() >= pendChain.size())
            break;
        i++;
    }
}

void PmergeMe::sortingResult()
{
    createComb();
    size_t i = 1;

    std::vector<int>::iterator it;
    int combIndex;
    while (i < combination.size())
    {
        combIndex = combination.at(i);
        if (combIndex >= (int)pendChain.size())
        {
            i++;
            continue;
        }
        it = std::lower_bound(mainChain.begin(), mainChain.end(), pendChain.at(combIndex));
        mainChain.insert(it, pendChain.at(combIndex));
        i++;
    }
}

void PmergeMe::start(int ac, char *av[])
{
    if (parseNumbers(ac, av) == false)
    {
        std::cerr << "invalid input ...plz enter correct input" << std::endl;
        numbers.clear();
        return;
    }
    // SortPairs();
    splitPairs();
    MergeSortPair(this->PairNumbers, 0, this->PairNumbers.size() - 1);
    fillMainChainAndPend();
    sortingResult();
    if (lastNumber != -1)
    {
        std::vector<int>::iterator it;
        it = std::lower_bound(mainChain.begin(), mainChain.end(), lastNumber);
        mainChain.insert(it, lastNumber);
    }
    printNumbers();
}

PmergeMe::~PmergeMe()
{
}
