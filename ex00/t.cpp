#include <iostream>
#include <map>
#include <string>

int main()
{

    std::map<int, std::string> m;
    m[1] = "one";
    m[2] = "two";
    m[3] = "three";
    m[8] = "eight";
    m[9] = "ninr";
    std::map<int, std::string>::iterator it = m.upper_bound(4);
    std::cout << it->first << " => " << it->second << std::endl;
    return (0);
}

