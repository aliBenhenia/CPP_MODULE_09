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
bool PmergeMe::isEven(size_t index)
{
    if (index % 2 == 0)
        return (true);
    return (false);
}


void PmergeMe::SortPairs()
{
    size_t i = 0;
    if (isOdd(numbers.size()))
    {
        this->lastNumber = numbers.back();
        numbers.pop_back();
    }
    else
        this->lastNumber = -1;
    while (i < numbers.size() - 1)
    {
        if (numbers[i] < numbers[i + 1]) 
            std::swap(numbers[i], numbers[i + 1]); 
        i += 2;
    }
}

void PmergeMe::splitPairs()
{
    size_t i = 0;
    if (isOdd(numbers.size()))
    {
        this->lastNumber = numbers.back();
        numbers.pop_back();
    }
    else
        this->lastNumber = -1;
    while (i < numbers.size() - 1) 
    {
        if (isEven(i)) 
            PairNumbers.push_back(std::make_pair(numbers[i], numbers[i + 1]));
        i++;
    }
    i = 0;
    
    while (i < PairNumbers.size())
    {
        if (PairNumbers[i].first < PairNumbers[i].second) 
            std::swap(PairNumbers[i].first, PairNumbers[i].second); 
        i++;
    }
}

void PmergeMe::Merge(std::vector<std::pair<int, int> > &PairNumbers, size_t start, size_t mid, size_t end)
{
    if (start == end && mid == end) 
        return;
    size_t lenArr1 = mid - start + 1; 
    size_t lenArr2 = end - mid;
    size_t i = 0;
    std::vector<std::pair<int, int> > leftArr(lenArr1);
    std::vector<std::pair<int, int> > rightArr(lenArr2);

    
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

size_t PmergeMe::getMiddle(size_t start, size_t end)
{
    return (start + (end - start) / 2);
}

void PmergeMe::MergeSortPair(std::vector<std::pair<int, int> > &PairNumbers, size_t start, size_t end)
{
    size_t mid;

    if (start >= end) 
        return;
    mid = getMiddle(start, end);          
    MergeSortPair(PairNumbers, start, mid);   
    MergeSortPair(PairNumbers, mid + 1, end); 
    Merge(PairNumbers, start, mid, end);      
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
    
    std::vector<int>::iterator it;
    std::vector<int>::iterator it2;
    std::cout << "after : ";
    for (it = mainChain.begin(); it != mainChain.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

std::vector<int> PmergeMe::genertaingJacobSequence()
{
    std::vector<int> jacobNumbers;
    jacobNumbers.push_back(0); 
    jacobNumbers.push_back(1);
    jacobNumbers.push_back(3); 
    jacobNumbers.push_back(5);
    jacobNumbers.push_back(11); 
    jacobNumbers.push_back(21);
    jacobNumbers.push_back(43);
    jacobNumbers.push_back(85); 
    jacobNumbers.push_back(171); 
    jacobNumbers.push_back(341);
    jacobNumbers.push_back(683);
    jacobNumbers.push_back(1365); 
    jacobNumbers.push_back(2731); 
    jacobNumbers.push_back(5461);   
    jacobNumbers.push_back(10923);   
    jacobNumbers.push_back(21845);  
    jacobNumbers.push_back(43691);  
    jacobNumbers.push_back(87381);   
    jacobNumbers.push_back(174763);  
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

void PmergeMe::printBeforeSort()
{
    std::vector<int>::iterator it;
    std::cout << "Before : ";
    for (it = numbers.begin(); it != numbers.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe::start_vector(int ac, char *av[])
{
    if (parseNumbers(ac, av) == false)
        throw "invalid input ...plz enter correct input";
    printBeforeSort();
    start1 = std::clock(); 
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
    end1 = std::clock();
    printNumbers();
}

void PmergeMe::splitPairsDeque()
{
    size_t i = 0;
    if (isOdd(numbersDeque.size()))
    {
        this->lastNumberDeque = numbersDeque.back();
        numbersDeque.pop_back();
    }
    else
        this->lastNumberDeque = -1;
    while (i < numbersDeque.size() - 1) 
    {
        if (isEven(i)) 
            PairNumbersDeque.push_back(std::make_pair(numbersDeque[i], numbersDeque[i + 1]));
        i++;
    }
    i = 0;
    
    while (i < PairNumbersDeque.size())
    {
        if (PairNumbersDeque[i].first < PairNumbersDeque[i].second)
            std::swap(PairNumbersDeque[i].first, PairNumbersDeque[i].second); 
        i++;
    }
}
bool PmergeMe::processNumberDeque(std::string input)
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
        numbersDeque.push_back(num);
    }
    if (numbersDeque.size() == 0)
        return (false);
    return (true);
}

bool PmergeMe::parseNumbersDeque(int ac, char *av[])
{
    int i = 1;
    if (ac == 2)
        return(false);
    while (i < ac)
    {
        if (processNumberDeque(av[i]) == false)
            return (false);
        i++;
    }
    return (true);
}

void PmergeMe::printNumbersDeque()
{
    
    std::deque<int>::iterator it;
    std::deque<int>::iterator it2;
    std::cout << "\n main chain: ";
    for (it = mainChainDeque.begin(); it != mainChainDeque.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe ::MergeDeque(std::deque<std::pair<int, int> > &PairNumbers, size_t start, size_t mid, size_t end)
{
    if (start == end && mid == end) 
        return;
    size_t lenArr1 = mid - start + 1;
    size_t lenArr2 = end - mid;
    size_t i = 0;
    std::deque<std::pair<int, int> > leftArr(lenArr1);
    std::deque<std::pair<int, int> > rightArr(lenArr2);

    
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
void PmergeMe::MergeSortPairDeque(std::deque<std::pair<int, int> > &PairNumbers, size_t start, size_t end)
{
    size_t mid;

    if (start >= end) 
        return;
    mid = getMiddle(start, end);          
    MergeSortPairDeque(PairNumbers, start, mid);   
    MergeSortPairDeque(PairNumbers, mid + 1, end); 
    MergeDeque(PairNumbers, start, mid, end);      
}

void PmergeMe::fillMainChainAndPendDeque()
{
    bool isFirstIteration = true;
    std::deque<std::pair<int, int> >::iterator it;

    for (it = PairNumbersDeque.begin(); it != PairNumbersDeque.end(); it++)
    {
        if (isFirstIteration)
        {
            mainChainDeque.push_back(it->second);
            mainChainDeque.push_back(it->first);
            pendChainDeque.push_back(it->second);
            isFirstIteration = false;
            continue;
        }
        mainChainDeque.push_back(it->first);
        pendChainDeque.push_back(it->second);
    }
}

void PmergeMe::createCombDeque()
{
    std::vector<int> jacobNumbers = genertaingJacobSequence(); 

    combinationDeque.push_back(0); 

    int i = 1; 
    while (i < 20) 
    {
        combinationDeque.push_back(jacobNumbers[i]); 
        int j = jacobNumbers[i - 1] + 1; 
        while (j < jacobNumbers[i]) 
        {
            combinationDeque.push_back(j); 
            j++; 
        }
        if (combinationDeque.size() >= pendChainDeque.size()) 
            break;
        i++; 
    }
}

void PmergeMe::sortingResultDeque()
{
    createCombDeque(); 
    size_t i = 1; 

    std::deque<int>::iterator it; 
    int combIndex; 
    while (i < combination.size()) 
    {
        combIndex = combination.at(i); 
        if (combIndex >= (int)pendChainDeque.size()) 
        {
            i++; 
            continue; 
        }
        it = std::lower_bound(mainChainDeque.begin(), mainChainDeque.end(), pendChainDeque.at(combIndex)); 
        mainChainDeque.insert(it, pendChainDeque.at(combIndex)); 
        i++; 
    }
}

void PmergeMe::printBeforeSortDeque()
{
    std::deque<int>::iterator it;
    std::cout << "Before sort: ";
    for (it = numbersDeque.begin(); it != numbersDeque.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}


void PmergeMe::start_deque(int ac, char *av[])
{
    if (parseNumbersDeque(ac, av) == false)
    {
        std::cerr << "invalid input ...plz enter correct input" << std::endl;
        numbersDeque.clear();
        return;
    }
    start2 = std::clock();
    splitPairsDeque();
    MergeSortPairDeque(this->PairNumbersDeque, 0, this->PairNumbersDeque.size() - 1);
    fillMainChainAndPendDeque();
    sortingResultDeque();
    if (lastNumberDeque != -1)
    {
        std::deque<int>::iterator it;
        it = std::lower_bound(mainChainDeque.begin(), mainChainDeque.end(), lastNumberDeque);
        mainChainDeque.insert(it, lastNumberDeque);
    }
    end2 = std::clock();
    
    
    
}

void PmergeMe::printTimeComplexity()
{
    double time1 = (static_cast<double>(end1 - start1)) / CLOCKS_PER_SEC;
    double time2 = (static_cast<double>(end2 - start2)) / CLOCKS_PER_SEC;
    std::cout << "Time to process a range of " << mainChain.size() << " elements with std::vector : " <<  time1 << " seconds" << std::endl;
    std::cout << "Time to process a range of " << mainChainDeque.size() << " elements with std::deque : " << time2 << " seconds" << std::endl;
}

PmergeMe::~PmergeMe()
{
}
