#include <iostream>
#include <vector>

class container {
  public:
   container(size_t size) : array{new int[size]{}}, size_{size} {}
   int* begin() {return array;}
   int* end() {return array + size_;}
   using reference = int&;
   using iterator = int*;

  private:
   int* array{nullptr};
   size_t size_{};
};

template<typename T>
void work_with_container(T cont) {
  // T::pointer begin_range = cont.begin(); // will be error 'T::pointer is not a type'
  typename T::iterator begin_range = cont.begin(); // keyword typename indicate that T::pointer is a type
  typename T::iterator end_range = cont.end();

  while(begin_range != end_range) {
    typename T::reference value = *begin_range;
    ++value;
    ++begin_range;
  }
}

template <typename T>
struct remove_const {
  typedef T type;
};

template <typename T>
struct remove_const<const T> {
  typedef T type;
};


template<typename T>
void work_with_remove_const(T value) {
  typename remove_const<decltype(value)>::type value_new = value;
  value_new = 40;
}

template<typename T>
void work_with_const(T value) {
  T value_new = value;
  // value_new = 40; // error if T == const
}

int main(int argc, char const *argv[]) {
  container c{4};

  work_with_container(c);
  std::vector<int> v(4, 100);
  work_with_container(v);
  int data{100};
  work_with_const<const int>(data);
  work_with_remove_const<const int>(data);
  return 0;
}
