#include <iostream>
#include <vector>

std::vector<int>::iterator findClosetNumberTop(std::vector<int>data, int num)
{
    std::vector<int>::iterator it = data.begin();
    while (it != data.end())
    {
        if (num < *it)
            return (it);
        it++;
    }
    return (data.end());// not found
}
int findClosetNumberBottom(std::vector<int>data, int num)
{
    std::vector<int>::iterator it = findClosetNumberTop(data, num);
    if (it != data.end())
    {
        if (*(it - 1) == num)
        {
            it--;
            it--;
            return (*it);
        }
        else
            return (*(--it));
    }
    return (0);
}
int main()
{
    std::vector<int>v;
    v.push_back(1);
    v.push_back(4);
    v.push_back(8);
    v.push_back(9);
    v.push_back(19);
    v.push_back(99);
    v.push_back(890);
    v.push_back(890445);
    std::cout << findClosetNumberBottom(v, 465) << std::endl;
    return 0;
}