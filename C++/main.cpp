#include <iostream>

#include "tests.h"
#include "FastaParser.h"
#include "WaveletTree.h"
#include <fstream>

using namespace std;

void test_time(int argc, char* argv[]) {
  std::string inFile(argv[1]);
  std::string parseDurationFile("./read.out");
  std::string buildDurationFile("./build.out");
  FastaParser fastaParser;
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  std::string str = fastaParser.parse(inFile);
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  WaveletTree tree(str);
  std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();

  ofstream parse_ostream;
  parse_ostream.open(parseDurationFile);
  auto parse_duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000;
  parse_ostream << parse_duration << endl;
  parse_ostream.close();

  ofstream build_ostream;
  build_ostream.open(buildDurationFile);
  auto build_duration = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count() / 1000;
  build_ostream << build_duration << endl;
  build_ostream.close();
}

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
//  test_time(argc, argv);
  run(argc, argv);
  return 0;
}
