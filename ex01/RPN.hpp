#ifndef RPNEVAL_HPP
#define RPNEVAL_HPP
#include <iostream>
#include <string>
#include <stack>

class RBN
{
    private:
        std::stack<int> numbers;
    public:
        RBN();
        RBN(const RBN &other);
        RBN &operator=(const RBN &other);
        void start(std::string expression);
        void calculeNumbers(char c);
        // bool checkIsValid(std::string expression);
        ~RBN();
};
bool isOpertor(char c);
#endif