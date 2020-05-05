#include <iostream>

int y (int& x) {return 1;} // overload for lvalue
int y (int&& x) {return 2;} // overload for rvalue

template<typename T>
int func1(T&& x) { return y(x);}

template<typename T>
int func2(T&& x) { return y(std::move(x));}

template<typename T>
int func3(T&& x) { return y(std::forward<T>(x));} //perfect forwarding, call corect overload function y 

template<typename T, typename ...Args>
T* make_object(Args&& ...arg) { // universal references 
   return new T {std::forward<Args...>(arg...)};
}

class String {
  public:
    String() = default;
    String(int size) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    String(const char* str) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    String(int count, char ch) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    String(const String&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    String(String&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    String operator =(const String&) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this; }
    String operator =(String&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this;}
};

class B {
  public:
    B() = default;
    B(const String& ref) : str{ref} {std::cout << __PRETTY_FUNCTION__ << std::endl;}
    B(String&& ref) : str{std::move(ref)} {std::cout << __PRETTY_FUNCTION__ << std::endl;}
    B(const B&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    B(B&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; }
    B& operator =(const B&) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this; }
    B& operator =(B&&) { std::cout << __PRETTY_FUNCTION__ << std::endl; return *this;}
    ~B() {std::cout << __PRETTY_FUNCTION__ << std::endl;}
  private:
    String str;
};

int main() {
  int i = 10;
  std::cout << func1(i) << func1(20) << std::endl;
  std::cout << func2(i) << func2(30) << std::endl;
  std::cout << func3(i) << func3(40) << std::endl;

  B* b_ptr = make_object<B>("Hello World");

  delete b_ptr;

  String str{"Some test"};

  b_ptr = make_object<B>(str);
  delete b_ptr;
  return 0;
}