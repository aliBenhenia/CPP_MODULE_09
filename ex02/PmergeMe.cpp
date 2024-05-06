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
}


PmergeMe::~PmergeMe()
{

}
