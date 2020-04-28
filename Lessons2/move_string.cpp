#include <iostream>
#include <cstring>

class string {
  public:
   string(const char* str) {
     std::cout << "string(const char* str)" << std::endl;
     auto len = strlen(str) + 1;
     str_ = new char[len];
     memcpy(str_, str, len);
   }

   string(const string& rhs) {
     std::cout << "string(const string& rhs)" << std::endl;
     auto len = strlen(rhs.str_) + 1;
     str_ = new char[len];
     memcpy(str_, rhs.str_, len);
   }

   // valid unspecified state
   string(string&& rhs) : str_{rhs.str_} {
     std::cout << "string(string&& rhs)" << std::endl;
     rhs.str_ = nullptr;
   }
   string& operator += (const string& rhs) {
     auto len_current = strlen(str_);
     auto len_rhs = strlen(rhs.str_);
     char* tmp_buff = new char[len_current + len_rhs + 1];
     memcpy(tmp_buff, str_, len_current);
     memcpy(tmp_buff + len_current, rhs.str_, len_rhs);
     delete[] str_;
     str_ = tmp_buff;
     return *this;
   }

  const char* data() const {
    return str_;
  }
  ~string() { delete [] str_; std::cout << "~string()" << std::endl;}
  private:
   char* str_{nullptr};
};

string operator + (const string& str1, const string& str2) {
  string tmp{str1};

  tmp += str2;
  return tmp;
}

int main(int argc, const char** argv) {
    string str1{"String1"};
    string str2{"String2"};

    string concat_string = str1 + str2; // maybe copy ellision call only one constructor insted two

    std::cout << concat_string.data() << std::endl;

    if (str1.data() != nullptr) {
      std::cout << "str1 is not empty" << std::endl;
    }

    string moved_string {std::move(str1)}; // moved data from str1 into moved_string
    // str1 currently in valid but unspecified state

    if (str1.data() == nullptr) {
      std::cout << "str1 is empty" << std::endl;
    }

    if (moved_string.data() != nullptr) {
      std::cout << "moved_string is not empty" << std::endl;
    }

    return 0;
}