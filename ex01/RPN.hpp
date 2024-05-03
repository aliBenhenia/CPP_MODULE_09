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
        ~RBN();
};

#endif