#include <iostream>

#include "tests.h"
#include "FastaParser.h"
#include "WaveletTree.h"
#include <fstream>
#include <cmath>

using namespace std;

void test_time(int argc, char* argv[]) {
  std::string inFile(argv[1]);
  std::string parseDurationFile("./read.out");
  std::string buildDurationFile("./build.out");
  std::string memoryFile("./mem.out");

  FastaParser fastaParser;
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  std::string str = fastaParser.parse(inFile);
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
  WaveletTree tree(str);
  std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();

  ofstream parse_ostream;
  parse_ostream.open(parseDurationFile);
  auto parse_duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / 1000.0;
  parse_ostream << parse_duration;
  parse_ostream.close();

  ofstream build_ostream;
  build_ostream.open(buildDurationFile);
  auto build_duration = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count() / 1000.0;
  build_ostream << build_duration;
  build_ostream.close();

  ofstream memory_ostream;
  memory_ostream.open(memoryFile);
  memory_ostream << tree.__sizeof() << endl;
  memory_ostream.close();
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
//    cout << "PID: " << ::getpid() << ", PPID: " << ::getppid() << endl;
//    int contNum;
//    cin >> contNum;
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

void test_query(int argc, char* argv[]) {
  std::string inFile(argv[1]);
  std::string rankFile("./rank.out");
  std::string selectFile("./select.out");
  std::string accessFile("./access.out");

  FastaParser fastaParser;
  std::string str = fastaParser.parse(inFile);
  WaveletTree tree(str);

  int halfSize = str.size()/2;
  int iters = std::stoi(argv[3]);
  int sqrtNum = (int) std::sqrt(halfSize);
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  for (int i = 0; i < iters; i++) {
    // rank
    tree.rank(str[0], halfSize);
  }
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < iters; i++) {
    // select
    tree.select(str[0], sqrtNum);
  }
  std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();

  for (int i = 0; i < iters; i++) {
    // access
    tree.access(halfSize);
  }
  std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();

  ofstream rank_ostream;
  rank_ostream.open(rankFile);
  auto rank_duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count() / iters / 1000.0;
  rank_ostream << rank_duration;
  rank_ostream.close();

  ofstream select_ostream;
  select_ostream.open(selectFile);
  auto select_duration = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count() / iters / 1000.0;
  select_ostream << select_duration;
  select_ostream.close();

  ofstream access_ostream;
  access_ostream.open(accessFile);
  auto access_duration = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count() / iters / 1000.0;
  access_ostream << access_duration;
  access_ostream.close();
}

int main(int argc, char* argv[]) {
//  test();
//  test_time(argc, argv);
  run(argc, argv);
//  test_query(argc, argv);
//  cout << "PID: " << ::getpid() << ", PPID: " << ::getppid() << endl;
//  int contNum;
//  cin >> contNum;
  return 0;
}
