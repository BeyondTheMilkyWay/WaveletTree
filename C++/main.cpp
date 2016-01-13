#include <iostream>

#include "tests.h"

using namespace std;

int main() {
//  cout << "Hello, World!" << endl;
//  std::string peterStr("Peter");
//  test_build(peterStr);
//  cout << endl << endl << endl;

  // rank
  const char *longArr = "Peter Piper picked a peck of pickled peppers";
  std::string longStr(longArr);
//  test_build(longStr);
  test_rank(longStr, 'e', 5);
  const char *exampleArr = "ahcbedghcfaehcgd";
  std::string exampleStr(exampleArr);
  test_rank(exampleStr, 'c', 9);
  std::string exampleStr2(exampleArr);
  test_build(exampleStr2);

  // select
  std::string exampleStr3(exampleArr);
  test_select(exampleStr3, 'c', 2);
  std::string exampleStr4(exampleArr);
  test_select(exampleStr4, 'h', 2);
  std::string longStr2(longArr);
  test_select(longStr2, 'e', 5);
  std::string exampleStr5(exampleArr);
  test_select(exampleStr5, 'h', 7);

  // access
  std::string exampleStr6(exampleArr);
  test_access(exampleStr6, 2);
  std::string exampleStr7(exampleArr);
  test_access(exampleStr7, 0);
  std::string longStr3(longArr);
  test_access(longStr3, 17);
  std::string exampleStr8(exampleArr);
  test_access(exampleStr8, 7);
  std::string exampleStr9(exampleArr);
  test_access(exampleStr9, 17);
  return 0;
}
