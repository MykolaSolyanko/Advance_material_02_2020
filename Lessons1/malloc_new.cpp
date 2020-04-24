#include <iostream>
#include <cstdlib>

class debug {
  public:
    debug() {std::cout << "debug()\n";} // default constructor
    debug(const debug&) {std::cout << "debug(const debug&)\n";} // copy constructor
    ~debug() {std::cout << "~debug()\n";} // destructor
};

int main(int argc, char const *argv[]) {
/* the new operator will perform two operations:
   1. Allocate memory
   2. The default constructor on the allocated memory will be called (object creation)
 */ 
  debug *ptr = new debug{};

/* The delete operator will perform two operations:
1. The destructor will be called (object destruction)
2. Free up occupied memory
 */
  delete ptr;

  // allocate raw memory without calling the constructor
  ptr = static_cast<debug *> (malloc(sizeof(debug)));

  // placement new, call constructor manually
  new(ptr) debug{};

  // call destructor manually
  ptr->~debug();
  // free memory but will not call the destructor
  free(ptr);
  return 0;
}
