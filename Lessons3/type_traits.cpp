
#include <iostream>
#include <type_traits>

class movable {
  public:
   movable() {std::cout << "movable()" << std::endl;}
   movable(const movable& ) {std::cout << "movable(const movable& )" << std::endl;}
   movable(movable&& ) {std::cout << "movable(movable&& )" << std::endl;}
};

class copyble {
  public:
   copyble() {std::cout << "copyble()" << std::endl;}
   copyble(const copyble& ) {std::cout << "copyble(const copyble& )" << std::endl;}
};

template<typename T>
void move_or_copy(T data) {
  if (std::is_move_constructible<T>::value) {
    std::cout << "moveble move_or_copy\n";
    T new_data{std::move(data)};
    return;
  }
  std::cout << "copyble move_or_copy\n";
  T new_data{data};
}

template<typename T>
void work_with_arithmetic(T data) {
  static_assert(std::is_arithmetic<T>::value, "is not arithmetic");
}

int main(int argc, char const *argv[]) {
  movable m;
  move_or_copy(m);

  copyble c;
  move_or_copy(c);

  int data;
  work_with_arithmetic(data);

  // work_with_arithmetic(m); // error not arithmetic

  return 0;
}
