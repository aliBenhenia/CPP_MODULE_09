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
        if (isEven(i)) // for the first element of pair
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
    std::vector<int> jacobNumbers = genertaingJacobSequence(); // generate the jacob sequence

    combination.push_back(0); // add the first element of jacob sequence

    int i = 1; // for the index of jacob sequence starting from the second element
    while (i < 20) // for the jacob sequence until the 20th element beacuse the jacob sequence has 20 elements
    {
        combination.push_back(jacobNumbers[i]); // add the element of jacob sequence
        int j = jacobNumbers[i - 1] + 1; // for the index of jacob sequence starting from the first element of jacob sequence and increment by 1 for the next element of jacob sequence until the current element of jacob sequence be less than the next element of jacob sequence in the jacob sequence 
        while (j < jacobNumbers[i]) // for the index of jacob sequence starting from the first element of jacob sequence and increment by 1 for the next element of jacob sequence until the current element of jacob sequence be less than the next element of jacob sequence in the jacob sequence
        {
            combination.push_back(j); // add the elements between the first element of jacob sequence and the next element of jacob sequence
            j++; 
        }
        if (combination.size() >= pendChain.size()) // if the combination size is greater than or equal to the pend chain size becasue the pend chain size is less than the combination size
            break;
        i++; // increment the index of jacob sequence
    }
}

void PmergeMe::sortingResult()
{
    createComb(); // create the combination based on the jacob sequence
    size_t i = 1; // for the index of combination starting from the second element because the first element of combination is already added in the main chain

    std::vector<int>::iterator it; // for the iterator of main chain
    int combIndex; // for the index of combination
    while (i < combination.size()) // for the combination until the last element of combination
    {
        combIndex = combination.at(i); // get the index of combination
        if (combIndex >= (int)pendChain.size()) // if the index of combination is greater than or equal to the pend chain size becasue the pend chain size is less than the combination size and we skip the element of pend chain
        {
            i++; // increment the index of combination because we skip the element of pend chain
            continue; // skip the element of pend chain
        }
        it = std::lower_bound(mainChain.begin(), mainChain.end(), pendChain.at(combIndex)); // find the position of the element of pend chain in the main chain
        mainChain.insert(it, pendChain.at(combIndex)); // insert the element of pend chain in the main chain
        i++; // increment the index of combination
    }
}
void PmergeMe::printBeforeSort()
{
    std::vector<int>::iterator it;
    std::cout << "Before sort: ";
    for (it = numbers.begin(); it != numbers.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}
void PmergeMe::printTimeComplexity()
{
    std::cout << "Time complexity: O(n log n)" << std::endl;
}
void PmergeMe::start_vector(int ac, char *av[])
{
    if (parseNumbers(ac, av) == false)
    {
        std::cerr << "invalid input ...plz enter correct input" << std::endl;
        numbers.clear();
        return;
    }
    printBeforeSort();
    std::clock_t start = std::clock();
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
    std::clock_t end = std::clock();
    printNumbers();
    // print the time complexity
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time complexity: " << time << " seconds" << std::endl;
}

void PmergeMe::splitPairsDeque()
{
    size_t i = 0;
    if (isOdd(numbersDeque.size()))// if the number of elements is odd mean the last element is not in pair
    {
        this->lastNumberDeque = numbersDeque.back();
        numbersDeque.pop_back();
    }
    else
        this->lastNumberDeque = -1;
    while (i < numbersDeque.size() - 1) // -1 for the last element of pair
    {
        if (isEven(i)) // for the first element of pair
            PairNumbersDeque.push_back(std::make_pair(numbersDeque[i], numbersDeque[i + 1]));
        i++;
    }
    i = 0;
    // sort the pair numbers
    while (i < PairNumbersDeque.size())
    {
        if (PairNumbersDeque[i].first < PairNumbersDeque[i].second) // for the first element of pair mean the first element is greater than the second element
            std::swap(PairNumbersDeque[i].first, PairNumbersDeque[i].second); // swap the two elements
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
    // print main chain and pend chain
    std::deque<int>::iterator it;
    std::deque<int>::iterator it2;
    std::cout << "\n main chain: ";
    for (it = mainChainDeque.begin(); it != mainChainDeque.end(); it++)
        std::cout << *it << " ";
    std::cout << std::endl;
}

void PmergeMe ::MergeDeque(std::deque<std::pair<int, int> > &PairNumbers, size_t start, size_t mid, size_t end)
{
    if (start == end && mid == end) // if the array has only one element
        return;
    size_t lenArr1 = mid - start + 1;
    size_t lenArr2 = end - mid;
    size_t i = 0;
    std::deque<std::pair<int, int> > leftArr(lenArr1);
    std::deque<std::pair<int, int> > rightArr(lenArr2);

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
void PmergeMe::MergeSortPairDeque(std::deque<std::pair<int, int> > &PairNumbers, size_t start, size_t end)
{
    size_t mid;

    if (start >= end) // if the array has only one element
        return;
    mid = getMiddle(start, end);          // for divide the array into two parts
    MergeSortPairDeque(PairNumbers, start, mid);   // for left part of array .. recursive call .. divide and conquer
    MergeSortPairDeque(PairNumbers, mid + 1, end); // for right part of array .. recursive call .. divide and conquer
    MergeDeque(PairNumbers, start, mid, end);      // merge the two parts of array .. conquer .. merge  the two parts of array
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
    std::vector<int> jacobNumbers = genertaingJacobSequence(); // generate the jacob sequence

    combinationDeque.push_back(0); // add the first element of jacob sequence

    int i = 1; // for the index of jacob sequence starting from the second element
    while (i < 20) // for the jacob sequence until the 20th element beacuse the jacob sequence has 20 elements
    {
        combinationDeque.push_back(jacobNumbers[i]); // add the element of jacob sequence
        int j = jacobNumbers[i - 1] + 1; // for the index of jacob sequence starting from the first element of jacob sequence and increment by 1 for the next element of jacob sequence until the current element of jacob sequence be less than the next element of jacob sequence in the jacob sequence 
        while (j < jacobNumbers[i]) // for the index of jacob sequence starting from the first element of jacob sequence and increment by 1 for the next element of jacob sequence until the current element of jacob sequence be less than the next element of jacob sequence in the jacob sequence
        {
            combinationDeque.push_back(j); // add the elements between the first element of jacob sequence and the next element of jacob sequence
            j++; 
        }
        if (combinationDeque.size() >= pendChainDeque.size()) // if the combination size is greater than or equal to the pend chain size becasue the pend chain size is less than the combination size
            break;
        i++; // increment the index of jacob sequence
    }
}

void PmergeMe::sortingResultDeque()
{
    createCombDeque(); // create the combination based on the jacob sequence
    size_t i = 1; // for the index of combination starting from the second element because the first element of combination is already added in the main chain

    std::deque<int>::iterator it; // for the iterator of main chain
    int combIndex; // for the index of combination
    while (i < combination.size()) // for the combination until the last element of combination
    {
        combIndex = combination.at(i); // get the index of combination
        if (combIndex >= (int)pendChainDeque.size()) // if the index of combination is greater than or equal to the pend chain size becasue the pend chain size is less than the combination size and we skip the element of pend chain
        {
            i++; // increment the index of combination because we skip the element of pend chain
            continue; // skip the element of pend chain
        }
        it = std::lower_bound(mainChainDeque.begin(), mainChainDeque.end(), pendChainDeque.at(combIndex)); // find the position of the element of pend chain in the main chain
        mainChainDeque.insert(it, pendChainDeque.at(combIndex)); // insert the element of pend chain in the main chain
        i++; // increment the index of combination
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

void PmergeMe::printTimeComplexityDeque()
{
    std::cout << "Time complexity: O(n log n)" << std::endl;
}

void PmergeMe::start_deque(int ac, char *av[])
{
    if (parseNumbersDeque(ac, av) == false)
    {
        std::cerr << "invalid input ...plz enter correct input" << std::endl;
        numbersDeque.clear();
        return;
    }
    printBeforeSortDeque();
    std::clock_t start = std::clock();
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
    std::clock_t end = std::clock();
    printNumbersDeque();
    // print the time complexity
    double time = (double)(end - start) / CLOCKS_PER_SEC;
    std::cout << "Time complexity: " << time << " seconds" << std::endl;
}

PmergeMe::~PmergeMe()
{
}
