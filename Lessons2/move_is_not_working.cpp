
#include <iostream>

class only_copied {
  public:
   // any of explicit add copy operations prevent generate move operations
   only_copied() {std::cout << "only_copied()" << std::endl;}
   only_copied(const only_copied& ) {std::cout << "only_copied(const only_copied& )" << std::endl;}
   // also explicit defined destructor prevent generate move operations
};

int main(int argc, const char** argv) {
  int value{10};

  int not_moved = std::move(value); // not moved, because build in type only copied
  // move semantics it's only idiom, not physically moved, and allplied for user types


  only_copied copy;

  only_copied try_move{std::move(copy)}; // call copy constructor instead of move constructor
  return 0;
}