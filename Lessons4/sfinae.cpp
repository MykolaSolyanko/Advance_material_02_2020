#include <iostream>
#include <string>

/*
using this function based on type_traits will not work since the if statement is a run-time operator,
and the compiler will process all branches of the if statement.
for example
auto str = convert(10); //error can not convert int to string, erroneous branch checks if (std::is_same<T, std::string>::value)
*/
// template<typename T>
// std::string convert(T value) {
//   if (std::is_same<T, std::string>::value) {
//     return value; // if T=string, then just return value, because we do not need a conversion
//   } else if (std::is_integral<T>::value) {
//     return std::to_string(value); // if T for example int using a standard function to convert a number to a string
//   }
//   return std::string(value); // for example T == const char*
// }

/*
the convert function uses the SFINAE approach,
i.e. instantiation error is not a compilation error
this used before C++17
*/
// template<typename T>
// typename std::enable_if<std::is_integral<T>::value, std::string>::type convert(T value) {
//   std::cout << "function\n";
//     return std::to_string(value);
//   // } else if (std::is_same<T, std::string>::value) {
//   //   return value;
//   // }
// }

// template<typename T>
// typename std::enable_if<std::is_same<T, std::string>::value, std::string>::type convert(T value) {
//   std::cout << "function2\n";
//     return value;
//   // } else if (std::is_same<T, std::string>::value) {
//   //   return value;
//   // }
// }

/*
 the same as above only uses a more compact form,
 available starting with C ++ 17
*/
template<typename T>
std::string convert(T value) {
  if constexpr (std::is_integral<T>::value) {
    return std::to_string(value);
  } else if constexpr (std::is_same<T, std::string>::value) {
    return value;
  }
}

int main() {
  std::cout << convert(10) << std::endl;
  std::cout << convert(std::string{"Hello World"}) << std::endl;
  return 0;
}