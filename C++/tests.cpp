//
// Created by Domagoj Stankovic on 1/12/16.
//

#include <iostream>
#include "WaveletTree.h"
#include "FastaParser.h"

using namespace std;

// prints elements of a vector
void print1(vector<char> &v) {
  for (char c : v) {
    cout << c;
  }
}

// recursively prints tree
void printTree(WaveletNode &node, int d) {
  if (node.isNull()) return;
  cout << d << ":" << endl << "alphabet ";
  print1(node.alphabet);
  cout << endl;
  cout << "bitarray: " << node.bitArray.toString();
  cout << endl << endl;
  printTree(*(node.left), d+1);
  printTree(*(node.right), d+1);
}

void test_build(std::string &str) {
  std::shared_ptr<WaveletTree> tree = std::make_shared<WaveletTree>(str);
  printTree(*(tree->getRoot()), 0);
}

void test_rank(std::shared_ptr<WaveletTree> tree, char q, int x) {
  cout << "Rank: " << tree->rank(q, x) << endl;
}

void test_rank(std::string &str, char q, int x) {
  std::shared_ptr<WaveletTree> tree = std::make_shared<WaveletTree>(str);
  test_rank(tree, q, x);
}

void test_select(std::shared_ptr<WaveletTree> tree, char q, int x) {
  cout << "Select: " << tree->select(q, x) << endl;
}

void test_select(std::string &str, char q, int x) {
  std::shared_ptr<WaveletTree> tree = std::make_shared<WaveletTree>(str);
  test_select(tree, q, x);
}

void test_access(std::shared_ptr<WaveletTree> tree, int x) {
  cout << "Access: " << tree->access(x) << endl;
}

void test_access(std::string &str, int x) {
  std::shared_ptr<WaveletTree> tree = std::make_shared<WaveletTree>(str);
  test_access(tree, x);
}

// tests file on a given path
void test_file(std::string &filePath) {
  cout << filePath << endl;
  FastaParser fastaParser;
  std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
  std::string file = fastaParser.parse(filePath);
  std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
//  cout << file << endl;

  std::shared_ptr<WaveletTree> tree = std::make_shared<WaveletTree>(file);
  std::chrono::high_resolution_clock::time_point t3 = std::chrono::high_resolution_clock::now();
//  cout << tree->getRoot()->bitArray.toString() << endl;

  int rank = tree->rank('G', 71);
  std::chrono::high_resolution_clock::time_point t4 = std::chrono::high_resolution_clock::now();

  int select = tree->select('G', 5);
  std::chrono::high_resolution_clock::time_point t5 = std::chrono::high_resolution_clock::now();

  char access = tree->access(70);
  std::chrono::high_resolution_clock::time_point t6 = std::chrono::high_resolution_clock::now();

  cout << "Rank: " << rank << endl;
  cout << "Select: " << select << endl;
  cout << "Access: " << access << endl;

  auto parse_duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
  cout << "Parse duration: " << parse_duration << endl;
  auto build_duration = std::chrono::duration_cast<std::chrono::microseconds>(t3 - t2).count();
  cout << "Build duration: " << build_duration << endl;
  auto rank_duration = std::chrono::duration_cast<std::chrono::microseconds>(t4 - t3).count();
  cout << "Rank duration: " << rank_duration << endl;
  auto select_duration = std::chrono::duration_cast<std::chrono::microseconds>(t5 - t4).count();
  cout << "Select duration: " << select_duration << endl;
  auto access_duration = std::chrono::duration_cast<std::chrono::microseconds>(t6 - t5).count();
  cout << "Access duration: " << access_duration << endl;
  auto total_duration = std::chrono::duration_cast<std::chrono::microseconds>(t6 - t1).count();
  cout << "Total duration: " << total_duration << endl << endl;
}

// general tests
void test() {
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

  // fasta
  std::string filePath6("/Users/dstankovic/Downloads/testCases/test_100.fa");
  test_file(filePath6);

  std::string filePath1("/Users/dstankovic/Downloads/testCases/test_1k.fa");
  test_file(filePath1);

  std::string filePath3("/Users/dstankovic/Downloads/testCases/test_10k.fa");
  test_file(filePath3);

  std::string filePath5("/Users/dstankovic/Downloads/testCases/test_100k.fa");
  test_file(filePath5);

  std::string filePath2("/Users/dstankovic/Downloads/testCases/test_1m.fa");
  test_file(filePath2);

  std::string filePath4("/Users/dstankovic/Downloads/testCases/test_10m.fa");
  test_file(filePath4);

  std::string filePath7("/Users/dstankovic/Downloads/testCases/test_100m.fa");
  test_file(filePath7);

  std::string filePath8("/Users/dstankovic/Downloads/testCases/test_dna_1k.fa");
  test_file(filePath8);

  std::string filePath9("/Users/dstankovic/Downloads/testCases/test_dna_100k.fa");
  test_file(filePath9);

  std::string filePath10("/Users/dstankovic/Downloads/testCases/test_dna_1m.fa");
  test_file(filePath10);

  std::string filePath11("/Users/dstankovic/Downloads/testCases/Escherichia_coli.fa");
  test_file(filePath11);
}