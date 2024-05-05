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
    (void)input;
    return (true);
}

// alg Ford-Johnson algorithm merge-insert sort algorithm
void PmergeMe::SortPairs()
{
    size i = 0;
    if (numbers.size() % 2 != 0)
    {
        this->lastNumber = numbers[numbers.size() - 1];
        numbers.pop_back();
    }
    while (i < numbers.size() - 1)
    {
        if (numbers[i] > numbers[i + 1])
            std::swap(numbers[i], numbers[i + 1]);
        i += 2;
    }
}

void PmergeMe::printNumbers()
{
    for (int i = 0; i < numbers.size(); i++)
    {
        std::cout << numbers[i] << " ";
    }
    if (lastNumber != 0)
        std::cout << lastNumber;
    std::cout << std::endl;
}

void PmergeMe::start(std::string input)
{
    if (parseNumbers(input) == false)
    {
        std::cout << "invalid input ...plz enter correct input" << std::endl;
        return;
    }
    SortPairs(); 
}


PmergeMe::~PmergeMe()
{

}
