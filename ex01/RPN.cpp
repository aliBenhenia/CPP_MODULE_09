#include "RPN.hpp"

RBN::RBN()
{
    // std::cout << "Default constructor called" << std::endl;
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

bool containOnlySpaces(std::string expression)
{
    int i = 0;
    while (expression[i])
    {
        if (expression[i] != ' ' && expression[i] != '\t')
            return (true);
        i++;
    }
    std::cout << "Error" << std::endl;
    return (false);
}

bool checkIsValid(std::string expression)
{
    if (containOnlySpaces(expression) == false)
        return (false);
    if (expression.empty())
    {
        std::cout << "Error" << std::endl;
        return (false);
    }
    if (expression.size() < 3) 
    {
        std::cout << "Error" << std::endl;
        return (false);
    }
    int i = 0;
    while (expression[i])
    {
        if (std::isdigit(expression[i]) && std::isdigit(expression[i + 1]))
        {
            std::cout << "Error" << std::endl;
            return (false);
        }
        if (std::isdigit(expression[i]) 
            || expression[i] == '+' 
            || expression[i] == '-' 
            || expression[i] == '*' 
            || expression[i] == '/' || expression[i] == ' ' || expression[i] == '\t')
        {
            i++;
        }
        else
        {
            std::cout << "Error" << std::endl;
            return (false);
        }
    }
    return (true);
}

bool isOpertor(char c)
{
    if (c == '+' || c == '-' || c == '*' || c == '/')
        return (true);
    return (false);
}

void RBN::calculeNumbers(char c)
{
    int x;
    int y;

    x = this->numbers.top();
    this->numbers.pop();
    y = this->numbers.top();
    this->numbers.pop();
    if (c == '+')
        this->numbers.push(x + y);
    else if (c == '-')
        this->numbers.push(y - x);
    else if (c == '*')
        this->numbers.push(x * y);
    else if (c == '/')
        this->numbers.push(y / x);
}
void RBN::start(std::string expression)
{
    if (checkIsValid(expression) == false)
       return;
    int i = 0;
    while (expression[i])
    {
        if (expression[i] == ' ' || expression[i] == '\t')
        {
            i++;
            continue;
        }
        if (std::isdigit(expression[i]))
            this->numbers.push(std::atoi(&expression[i]));
        else if (isOpertor(expression[i]))
            calculeNumbers(expression[i]);
        i++;
    }
    std::cout << this->numbers.top() << std::endl;
}

RBN::~RBN()
{
    // std::cout << "Destructor called" << std::endl;
}
