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

bool PmergeMe::parseNumbers(std::string input)
{
    std::string number;
    size_t i = 0;

    while (i < input.size())
    {
        if (input[i] == ' ')
        {
            if (number.size() > 0)
            {
                numbers.push_back(std::stoi(number));
                number.clear();
            }
        }
        else if (std::isdigit(input[i]) || input[i] == '-')
            number += input[i];
        else
            return (false);
        i++;
    }
    if (number.size() > 0)
        numbers.push_back(std::stoi(number));
    if (numbers.size() == 0)
        return (false);
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
    while (i < numbers.size())
    {
        if (numbers[i] > numbers[i + 1])
            std::swap(numbers[i], numbers[i + 1]);
        i += 2;
    }
}

void PmergeMe::splitPairs()
{
    size_t i = 0;

    while (i < numbers.size())
    {
        PairNumbers.push_back(std::make_pair(numbers[i], numbers[i + 1]));
        i += 2;
    }
}

void PmergeMe::Merge(std::vector<std::pair<int, int> > &PairNumbers, size_t start, size_t mid, size_t end)
{

// for the first part of array and second part of array..so objectif is to merge the two parts of array
    size_t i = 0;
    size_t j = 0;

    while (i < mid - start + 1)// copy the first part of array to first vector
    {
        first.push_back(PairNumbers[start + i].first); // copy the first part of array to first vector
        second.push_back(PairNumbers[start + i].second); // copy the second part of array to second vector
        i++;
    }
    while (j < end - mid)  // copy the second part of array to second vector
    {
        first.push_back(PairNumbers[mid + 1 + j].first); // copy the first part of array to first vector
        second.push_back(PairNumbers[mid + 1 + j].second); // copy the second part of array to second vector
        j++;
    }
    // merge the two parts of array
    i = 0;
    j = 0;
    size_t k = start;
    while (i < first.size() && j < second.size())
    {
        if (first[i] <= second[j]) // compare the two parts of array and merge them
        {
            PairNumbers[k].first = first[i];
            PairNumbers[k].second = second[i]; 
            i++;
        }
        else
        {
            PairNumbers[k].first = second[j];
            PairNumbers[k].second = first[j];
            j++;
        }
        k++;
    }
   
}

void PmergeMe::MergeSortPair(std::vector<std::pair<int, int> > &PairNumbers, size_t start, size_t end)
{
    int mid;

    if (start >= end)// base case for recursion when the array is divided into single element
        return;
    mid = (start + end) / 2; // for divide the array into two parts 
    MergeSortPair(PairNumbers, start, mid); // for left part of array .. recursive call .. divide and conquer
    MergeSortPair(PairNumbers, mid + 1, end); // for right part of array .. recursive call .. divide and conquer
    Merge(PairNumbers, start, mid, end); // merge the two parts of array .. conquer .. merge  the two parts of array 
}

void PmergeMe::printNumbers()
{
    size_t i = 0;

    while (i < PairNumbers.size())
    {
        std::cout << PairNumbers[i].first << " " << PairNumbers[i].second << std::endl;
        i++;
    }
    if (lastNumber != 0)
        std::cout << lastNumber << std::endl;
}

void PmergeMe::start(std::string input)
{
    if (parseNumbers(input) == false)
    {
        std::cout << "invalid input ...plz enter correct input" << std::endl;
        return;
    }
    SortPairs();
    splitPairs();
    MergeSortPair(this->PairNumbers, 0, this->PairNumbers.size() - 1);
}


PmergeMe::~PmergeMe()
{
}
