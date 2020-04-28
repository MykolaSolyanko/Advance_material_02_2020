#include <cstring>
#include <iostream>

template<typename T>
class Vector {
  public:
    // this constructor allocates memory using the new operator, which will call the default constructor for custom types
    Vector(size_t count) : data_{new T[count]{}}, capacity_{count}, count_{count}
    {
        std::cout << __PRETTY_FUNCTION__ <<std::endl;
    }
    // this constructor allocates memory using the C operator malloc function,
    // which will allocate raw memory and not call the constructor for custom types
    Vector() : data_{static_cast<T*>(malloc(capacity_ * sizeof(T)))} {
        std::cout << __PRETTY_FUNCTION__ <<std::endl;
    }

    Vector(const Vector& rhs) : capacity_{rhs.capacity_}, data_{new T[rhs.count_]{}}, count_{rhs.count_}
    {std::cout << __PRETTY_FUNCTION__ <<std::endl;}

    // move constructor should leave the movable object in a valid indefinite state
    Vector(Vector&& rhs) : capacity_{rhs.capacity_}, data_{rhs.data_}, count_{rhs.count_}
    {
        std::cout << __PRETTY_FUNCTION__ <<std::endl;
        rhs.data_ = nullptr;
        rhs.capacity_ = 0;
        rhs.count_ = 0;
    }

    Vector& operator=(Vector&& rhs) { // move operator should leave the movable object in a valid indefinite state
        std::cout << __PRETTY_FUNCTION__ <<std::endl;
        data_ = rhs.data_;
        capacity_ = rhs.capacity_;
        count_ = rhs.count_;
        rhs.data_ = nullptr;
        rhs.capacity_ = 0;
        rhs.count_ = 0;   
        return *this;
    }
    Vector& operator=(const Vector& rhs) { // copy operator
        std::cout << __PRETTY_FUNCTION__ <<std::endl;
        if (this == &rhs) {return *this;}
        count_ = rhs.count_;
        capacity_ = rhs.capacity_;
        data_ = new T[capacity_];
       
      return *this;
    }
    void push_back(const T& value) { // will be called when passing lvalue
     std::cout << __PRETTY_FUNCTION__ << count_ <<std::endl;
      data_[count_++] = value;
    }

    void push_back(T&& value) { // will be called when passing rvalue
      std::cout << __PRETTY_FUNCTION__ << count_ <<std::endl;
      // if you do not specify std :: move,
      // then the assignment operator will be called instead of the moving operator
      data_[count_++] = std::move(value);
    }
    ~Vector() {
        delete[] data_;
    }
    T* GetData() {
        return data_;
    }
  private:
    size_t capacity_{4};
    T* data_{};
    size_t count_{};
};


class Log {
  public:
   Log() {std::cout << __PRETTY_FUNCTION__ <<std::endl;}
   Log(const Log&) {std::cout << __PRETTY_FUNCTION__ <<std::endl;}
   Log(Log&&) {std::cout << __PRETTY_FUNCTION__ <<std::endl;}
   Log& operator=(const Log&) {std::cout << __PRETTY_FUNCTION__ <<std::endl; return *this;}
   Log& operator=(Log&&) {std::cout << __PRETTY_FUNCTION__ <<std::endl; return *this;}
};


template<typename T>
Vector<T> make(size_t count) {
  // return std::move(Vector<T>{}); // prevent optimization RVO 
  return Vector<T>{}; // will be RVO
}

// case NRVO
template<typename T>
Vector<T> make_nrvo(size_t count) {
  Vector<T> name{};
  return name; // will be NRVO (name return value optimization)
}

// case NRVO
template<typename T>
Vector<T> make_nrvo1(size_t count) {
  Vector<T> name{};
  if (count == 0) {
    return name; // will be NRVO
  }
  return name; // will be NRVO
}

// case when there will be no NRVO
// NRVO and RVO are possible when your return context is the same(rvalue or lvalue, but not both).
template<typename T>
Vector<T> make_no_nrvo(size_t count) {
  Vector<T> name{};
  if (count == 0) {
    return Vector<T>{}; // will be no NRVO
  }
  return name; // will be no NRVO because there will be a different context
}

// NRVO/RVO is a copy ellision 
int main(int argc, char const *argv[]) {

    auto v_copy = make<Log>(2); // only one constructor will be called instead of two (RVO)

    auto v_copy_nrvo = make_nrvo<Log>(10); // only one constructor will be called instead of two (NRVO)

    auto v_copy_no_nrvo = make_no_nrvo<Log>(10); // call two constructor: one constructor inside make_no_nrvo function and second one move constructor 
 
    Vector<Log> v{};
    v.push_back(Log{}); // called push_back(T&& value)

    Log l;

    // converting lvalue -> rvalue
    v.push_back(std::move(l)); // called push_back(T&& value)

    Log next;
    v.push_back(next); // // called push_back(const T& value)
    
    return 0;
}