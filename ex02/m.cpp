#include <iostream>
#include <vector>

void print(int i)
{
    if (i == 0)
        return;
    print(i - 1);
    std::cout << "last print:" << i << std::endl;
}

int main()
{
    print(5);
    return 0;
}