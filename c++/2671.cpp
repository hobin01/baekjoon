#include <iostream>
#include <regex>
#include <string>

int main()
{
    std::string s; std::cin >> s;
    std::regex re("(100+1+|01)+");
    std::regex_match(s, re) ? std::cout << "SUBMARINE" : std::cout << "NOISE";
}