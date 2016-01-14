#include <iostream>

#include "tests.h"
#include "FastaParser.h"
#include "WaveletTree.h"
#include <fstream>

using namespace std;

void run(int argc, char* argv[]) {
  if (argc < 4) {
    cout << "Invalid arguments" << endl;
    return;
  }
  std::string inFile(argv[1]);
  std::string outFile(argv[2]);
  std::string task(argv[3]);
  FastaParser fastaParser;
  std::string str = fastaParser.parse(inFile);
  ofstream ostream;
  ostream.open(outFile);
  if (task.compare("build") == 0) {
    // build
    WaveletTree tree(str);
  } else if (task.compare("rank") == 0) {
    // rank
    if (argc < 6) {
      cout << "Invalid arguments" << endl;
      ostream.close();
      return;
    }
    char q = argv[4][0];
    int x = std::atoi(argv[5]);
    WaveletTree tree(str);
    int rank = tree.rank(q, x);
    ostream << rank << endl;
    cout << rank << endl;
  } else if (task.compare("select") == 0) {
    // select
    if (argc < 6) {
      cout << "Invalid arguments" << endl;
      ostream.close();
      return;
    }
    char q = argv[4][0];
    int x = std::atoi(argv[5]);
    WaveletTree tree(str);
    int select = tree.select(q, x);
    ostream << select << endl;
    cout << select << endl;
  } else if (task.compare("access") == 0) {
    // access
    if (argc < 5) {
      cout << "Invalid arguments" << endl;
      ostream.close();
      return;
    }
    int x = std::atoi(argv[4]);
    WaveletTree tree(str);
    char access = tree.access(x);
    ostream << access << endl;
    cout << access << endl;
  } else {
    cout << "Task does not exist!" << endl;
  }
  ostream.close();
}

int main(int argc, char* argv[]) {
//  test();
  run(argc, argv);
  return 0;
}
