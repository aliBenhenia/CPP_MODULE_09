#include "RPN.hpp"

RBN::RBN()
{
    std::cout << "Default constructor called" << std::endl;
}

RBN::RBN(const RBN &other)
{
    this->numbers = other.numbers;
}

RBN &RBN::operator=(const RBN &other)
{
    this->numbers = other.numbers;
    return (*this);
}

RBN::~RBN()
{
    std::cout << "Destructor called" << std::endl;
}
