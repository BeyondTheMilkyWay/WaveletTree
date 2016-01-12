#include <iostream>

#include "tests.h"

using namespace std;

int main() {
//  cout << "Hello, World!" << endl;
//  std::string peterStr("Peter");
//  test1(peterStr);
//  cout << endl << endl << endl;
  std::string longStr("Peter Piper picked a peck of pickled peppers");
//  test1(longStr);
  test_rank(longStr, 'e', 5);
  std::string exampleStr("ahcbedghcfaehcgd");
  test_rank(exampleStr, 'c', 9);
  return 0;
}
