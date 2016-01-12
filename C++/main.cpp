#include <iostream>
#include "WaveletTree.h"

using namespace std;

void printTree(WaveletNode &node, int d);

int main() {
  std::string str("Peter$");
  std::shared_ptr<WaveletTree> tree = std::make_shared<WaveletTree>(str);
  printTree(*(tree->getRoot()), 0);
  cout << "Hello, World!" << endl;
  return 0;
}

void print1(std::vector<char> &v) {
  for (char c : v) {
    cout << c;
  }
}

void printTree(WaveletNode &node, int d) {
  if (node.isNull()) return;
  cout << d << ": ";
  print1(node.alphabet);
  cout << endl;
  printTree(*(node.left), d+1);
  printTree(*(node.right), d+1);
}
