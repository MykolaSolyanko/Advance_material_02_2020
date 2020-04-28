
#include <iostream>

#include <string>

class debug {
  public:
   debug(int i_) : i{i_} {
     std::cout << "ctr " << i << std::endl;
     std::cout << "debug(int i)\n";
   }

   ~debug() {
     std::cout << "dest " << i << std::endl;
     std::cout << "~debug()\n";
    }

   debug(const debug&) {std::cout << "debug(const debug&)\n";}

  private:
    int i;
};

// this function will return rvalue result
debug get_value() { 
  debug d{3};
  return d;
}

int main(int argc, char const *argv[]) {
  debug d{1}; // d is lvalue(d has storage location - memory)
  debug{2}; // this is rvalue, because in this context a temporary variable will be used
            // here call constructor and destructor for temporary value

  std::string str1{"String 1"}; // str1 is lvalue
  std::string str2{"String 2"}; // str2 is lvalue
  std::string res = str1 + str2; // the result of concatenating two strings (str1 + str2) is rvalue

  debug& lvalue_ref = d; // lvalue_ref is a lvalue references, which can only refer to lvalue

  // debug& lvalue_ref_ = debug{3}; // compiler error: lvalue reference to type 'debug' cannot bind to a temporary(rvalue) of type 'debug'
  std::cout << "exit from program" << std::endl;
  // here called destructor for lvalue object d
  return 0;
}
