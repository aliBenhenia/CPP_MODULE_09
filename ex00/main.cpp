#include <iostream>
#include <vector>
#include <map>
#include <string>

int main()
{
    std::map<std::string, int> data;
    data["aya"] = 9;
    data["issam"] = 8;
    data["ali"] = 7764;
    data["jawad"] = 5;
    data["emrah"] = 56;
 
    std::map<std::string, int>::iterator it = data.begin();
    // while (it != data.end())
    // {
    //     std::cout << "address:" << &it->first << " = " << it->second << std::endl;
    //     it++;
    // }
    std::vector<char>v;
    v.push_back('1');
    v.push_back('3');
    v.push_back('5');
    v.push_back('6');
    int i = 0;
    while (i < v.size())
    {
        std::cout << "address:" << &v[i] << " = " << v[i]<< std::endl;
        i++;
    }
    return 0;
}