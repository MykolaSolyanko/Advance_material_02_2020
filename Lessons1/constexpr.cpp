#include <iostream>

/*
The result of this function can be calculated both at the compilation stage
and at the execution stage depending on the arguments
of this function (compile time arguments or runtime)
*/
template<typename T, std::size_t N>
constexpr unsigned short calc_sum(T (&arr_begin)[N]) {
  unsigned short sum{};
  for(auto var : arr_begin) {
    sum += var;
  }
  return sum;
}

int main(int argc, char const *argv[]) {
  // constexpr is the same as const. But constexpr is compile time const(only compile time).
  // const could be compile time(compiler optimization) or runtime
  constexpr unsigned short array_compile_time[5] {2, 1, 3, 4, 5}; // compile time array
  constexpr unsigned short sum = calc_sum(array_compile_time); // calc_sum will be computed on compile time because array is compile time expression
  std::cout << sum << std::endl;
  static_assert(sum == 15); // static_assert is a compile time checker

  unsigned int sum_ = calc_sum(array_compile_time); // calc_sum will be computed on compile time because array is compile time expression
  // sum_ is a runtime variable, but compiler could optimize this variable(O2 or O3)
  // static_assert(sum_ == 15); // compile error because static_assert used only with compiler time expression

  constexpr size_t kArraySize{5}; // compile time constant 
  int array_runtime[kArraySize]; // runtime array
  for (size_t i = 0; i < kArraySize; i++) {
    std::cin >> array_runtime[i];
  }
  
  unsigned int sum_runtime = calc_sum(array_compile_time); // the result of this function will be known at run time
  return 0;
}
