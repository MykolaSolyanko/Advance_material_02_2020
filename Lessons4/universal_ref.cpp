
struct Point {
 int x{};
 int y{};
};


// https://cppinsights.io/

int main(int argc, const char** argv) {
  auto&& ref = Point{1, 1}; // ref is &&-> rvalue reference (&& && -> &&)

  Point p;

  auto&& l_ref = p; // l_ref is &-> lvalue references (&& &-> &)

  int a;

  auto&& uref = a; // lvalue ref

  auto&& uref = a + 10; // rvalue ref
  return 0;
}