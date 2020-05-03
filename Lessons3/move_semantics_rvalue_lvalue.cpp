#include <iostream>

class base {
  public:
   base() {std::cout << "base()" << std::endl;}
   base(const base& ) {std::cout << "base(const base& )" << std::endl;}
   base(base&& ) {std::cout << "base(base&& )" << std::endl;}
};


class derived: public base {
  public:
   derived() {std::cout << "derived()" << std::endl;}
   derived(const derived& rhs): base(rhs) {std::cout << "derived(const derived& )" << std::endl;}
   // derived(derived&& rhs) : base(rhs) {std::cout << "derived(derived&& )" << std::endl;} // incorrect call base constructor
   derived(derived&& rhs) : base(std::move(rhs)) {std::cout << "derived(derived&& )" << std::endl;} 
};

void accept_value(const base& lvalue_ref) {
  std::cout << "accept lvalue" << std::endl;
}

void accept_value(base&& rvalue_ref) { // 
  std::cout << "accept rvalue" << std::endl;
}

void forward_data(base&& data) {
  accept_value(data); // call lvalue overload accept_value
  accept_value(std::move(data)); // // call rvalue overload accept_value
}

class ref_qualified {
  public:
   ref_qualified(int a) : a_{a} {std::cout << "ref_qualified(int a)" << std::endl;}
   ref_qualified(const ref_qualified& ) {std::cout << "ref_qualified(const ref_qualified& )" << std::endl;}
   ref_qualified(ref_qualified&& ) {std::cout << "ref_qualified(ref_qualified&& )" << std::endl;}
   int& get_value() & {  // work with lvalue object
     std::cout << "work with lvalue\n";
     return a_;
   }

   int get_value() && {  // work with rvalue object
     std::cout << "work with rvalue\n";
     return a_;
   }

  private:
   int a_{10};
};

int main(int argc, char const *argv[]) {
    derived d;

    derived d_copy{std::move(d)};

    forward_data(std::move(d));

    ref_qualified r{10};
    std::cout << r.get_value() << std::endl; // call lvalue overload
    std::cout << ref_qualified(30).get_value() << std::endl; // call rvalue overload
    return 0;
}
