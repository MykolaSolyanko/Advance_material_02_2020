#include <iostream>

template <typename T>
struct Del_default {
  void operator()(T* data) {
    delete data;
  }
};

template <typename T>
struct Del_default <T[]> { // partial specialization for array
  void operator()(T* data) {
    delete [] data;
  }
};

template<typename T, typename Del = Del_default<T>>
class unique_ptr {
 public:
   unique_ptr(T*ptr) : data{ptr} {}
   ~unique_ptr() { del(data); }
 private:
   T*data;
   Del del;
};

template<typename T, typename Del>
class unique_ptr <T[], Del> {
  public:
   unique_ptr(T*ptr) : data{ptr} {}
   ~unique_ptr() { del(data);}
  private:
    T*data;
    Del del;
};

class debug {
  public:
   debug() {std::cout << "debug\n";}
   ~debug() {std::cout << "~debug\n";}
};

int main(int argc, char const *argv[]) {
  debug* ptr = new debug{};
  unique_ptr<debug> uptr{ptr};

  std::cout << "before\n";

  debug* ptr_arr = new debug[10];
  unique_ptr<debug[]> uptr_ar{ptr_arr};
  return 0;
}
