#include <iostream>

class debug {
  public:
   debug(int i) {std::cout << "debug(int i)" << std::endl;}
   debug(const debug& ) {std::cout << "debug(const debug& )" << std::endl;}
   debug(debug&& ) {std::cout << "debug(debug&& )" << std::endl;}
   debug& operator=(const debug&) {
    std::cout << "debug& operator=(const debug&)" << std::endl;
    return *this;
   }
   debug& operator=(debug&& ) {
     std::cout << "debug& operator=(debug&& )" << std::endl;
     return *this;
   }
   void set_some_value() {}
   int get_some_value() const {return 10;}
};

template <typename T>
void move_swap(T a, T b) { // this swap will be call move operations (move constructor - move operator)
  T t{std::move(a)}; //std::move is just static_cast<T&&>(a) // & -> && // lvalue reference -> rvalue reference
  a = std::move(b);
  b = std::move(t);
}

template <typename T>
void copy_swap(T a, T b) { // this swap will call copy operations (copy constructor- move operator)
  T t{a};
  a = b;
  b = t;
}

debug get_debug_value() {
  debug d{2};
  return d;
}

void accept_value(const debug& lvalue_ref) {
  std::cout << "accept lvalue" << std::endl;
  std::cout << lvalue_ref.get_some_value() << std::endl;
  // lvalue_ref.set_some_value(); compile error

}

void accept_value(debug&& rvalue_ref) {
  std::cout << "accept rvalue" << std::endl;
  std::cout << rvalue_ref.get_some_value() << std::endl;
  rvalue_ref.set_some_value();

}

int main(int argc, const char** argv) {
  debug d{1};

  debug d_copy{d}; // call copy constructor
  debug d_move{std::move(d)}; // call move constructor

  debug&& rvalue_references = get_debug_value(); // rvalue references to rvalue (temporary object)

  debug&& expired_value = std::move(d_move); // nothing will be called it's just a references

  accept_value(d_move); // call lvalue references overload
  accept_value(std::move(expired_value)); // call rvalue references overload

  accept_value(debug{3}); // call rvalue references overload

  copy_swap(d_copy, d_move); // call copy operations

  move_swap(d_copy, d_move); // call move operations
  return 0;
}