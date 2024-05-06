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

void PmergeMe::printNumbers()
{
    for (size_t i = 0; i < numbers.size(); i++)
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
