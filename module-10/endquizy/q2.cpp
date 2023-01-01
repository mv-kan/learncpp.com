#include <iostream>
#include <string>
#include <regex>
int main()
{
  std::string str{ "I saw a red car yesterday." };

  str = std::regex_replace(str, std::regex("red"), "blue"); 

  std::cout << str << '\n'; // I saw a blue car yesterday.

  return 0;
}