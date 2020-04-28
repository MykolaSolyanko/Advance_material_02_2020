
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
   void set_value(int new_value) {i = new_value;}
   int get_value() const {return i;}
  private:
    int i;
};

// this function will return rvalue result
debug get_value() { 
  debug d{3};
  return d;
}

void accept_only_lvalue(debug& lvalue) {
  std::cout << "accept only lvalue object\n";
  lvalue.set_value(10);
  std::cout << lvalue.get_value() << std::endl;
}

void accept_only_rvalue(const debug& rvalue) { // accept temporary object
  std::cout << "accept only rvalue object\n";
  // rvalue.set_value(20); // compile error: for const object should called only const method
  std::cout << rvalue.get_value() << std::endl;
}


void accept_both_rvalue_and_lvalue(const debug& rvalue_rvalue) {
  std::cout << "accept both rvalue object and lvalue object\n";
}

int main(int argc, char const *argv[]) {
  debug d{1}; // d is lvalue(d has storage location - memory)
  debug{2}; // this is rvalue, because in this context a temporary variable will be used
            // here call constructor and destructor for temporary value
  const debug& const_ref = debug{3}; // live time prolongation rvalue(temporary object)
                                     // call constructor

  accept_only_lvalue(d);
  accept_only_rvalue(debug{20});

  accept_both_rvalue_and_lvalue(d);
  accept_both_rvalue_and_lvalue(debug{40});

  get_value(); // return rvalue
               // call constructor and destructor for temporary object
  const debug& func_ret_value = get_value(); // live time prolongation
                                             // call constructor
  std::cout << "exit from program" << std::endl;
  // here called destructor for lvalue object d and for const object  const_ref and for func_ret_value
  return 0;
}
