#include <iostream>

#include "tests.h"

using namespace std;

int main() {
  cout << "Hello, World!" << endl;
  std::string peterStr("Peter");
//  test1(peterStr);
  cout << endl << endl << endl;
  std::string longStr("Peter Piper picked a peck of pickled peppers");
  test1(longStr);
  return 0;
}
