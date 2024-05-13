#include <iostream>
#include <vector>


template <typename T1, typename T2>
class MyPair
{

    public:
        T1 first;
        T2 second;
        MyPair(){}
        MyPair(T1 first, T2 second)
        {
            this->first = first;
            this->second = second;
        }
};

template <typename T1, typename T2>
MyPair<T1, T2> makePair(T1 first, T2 second)
{
    return MyPair<int,int>(first, second);
}

int main()
{
    MyPair<int, int> myPair(1, 2);
    std::cout << myPair.first << " " << myPair.second << std::endl;
    std::vector<MyPair<int, int> > myVector;

    myVector.push_back(makePair(1, 2));
    myVector.push_back(makePair(3, 4));
    myVector.push_back(makePair(5, 6));


    std::vector<MyPair<int, int> >::iterator it;

    it = myVector.begin();
    while (it != myVector.end())
    {
        std::cout << it->first << " " << it->second << std::endl;
        it++;
    }
    return 0;
}