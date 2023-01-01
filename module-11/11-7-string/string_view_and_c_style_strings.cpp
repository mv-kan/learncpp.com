#include <cstring>
#include <iostream>
#include <string_view>

int main()
{
  std::string_view str{ "balloon" };


  // remove the "b"
  std.remove_prefix(1);
  // remove the "oon"
  str.remove_suffix(3);
  // Remember that the above doesn't modify the string, it only changes
  // the region that str is observing.

  std::cout << str << " has " << std::strlen(str.data()) << " letter(s)\n";
  std::cout << "str is " << str << '\n';
  std::cout << "str.data() is " << str.data() << '\n';
  // for string view to properly work with c style string we have to ensure that string has null terminator otherwise
  // it will be UB  
  return 0;
}