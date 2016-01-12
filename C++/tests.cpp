//
// Created by Domagoj Stankovic on 1/12/16.
//

#include <iostream>
#include "WaveletTree.h"

using namespace std;

void print1(vector<char> &v) {
  for (char c : v) {
    cout << c;
  }
}

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

void test1(std::string &str) {
  std::shared_ptr<WaveletTree> tree = std::make_shared<WaveletTree>(str);
  printTree(*(tree->getRoot()), 0);
}

void test_rank(std::string &str, char q, int x) {
  std::shared_ptr<WaveletTree> tree = std::make_shared<WaveletTree>(str);
  cout << "Rank: " << tree->rank(q, x) << endl;
}