//
// Created by Domagoj Stankovic on 1/11/16.
//

#include <set>
#include <map>
#include <iostream>
#include "WaveletTree.h"
#include "WaveletNodeNull.h"

bool code(std::map<char, bool> &map, std::vector<char> &alphabet, char q) {
  if (map.find(q) == map.end()) {
    // key doesn't exist
    map[q] = WaveletNode::bitcode(alphabet, q);
  }
  return map[q];
}

WaveletNodeP build2(std::string &str, int l, int r, std::vector<char> &alphabet) {
  if (alphabet.size() <= 1) {
    return std::make_shared<WaveletNodeNull>(alphabet);
  }
  BitArray bitArray(r - l + 1);
  std::map<char, bool> map;
  for (int i = l; i <= r; i++) {
    bitArray.set(i - l, code(map, alphabet, str[i]));
  }
  std::vector<char> lAlphabet(alphabet.begin(), alphabet.begin() + alphabet.size() / 2);
  int mid = (l + r - 1)/2;
  std::cout << "l: " << l << " r: " << r << " mid= " << mid << std::endl;
  WaveletNodeP left = build2(str, l, mid, lAlphabet);
  std::vector<char> rAlphabet(alphabet.begin() + alphabet.size() / 2, alphabet.end());
  WaveletNodeP right = build2(str, mid + 1, r, rAlphabet);
  std::shared_ptr<WaveletNode> node = std::make_shared<WaveletNode>(bitArray, alphabet, left, right);
  left->parent = node;
  right->parent = node;
  return node;
}

void WaveletTree::build(std::string &str) {
  // extract and sort alphabet
  std::cout<<"build"<<std::endl;
  std::set<char> chars;
  for (char c : str) {
    chars.insert(c);
  }
  std::vector<char> alphabet;
  for (char c : chars) {
    if (c == ' ') {
      alphabet.push_back('_');
    } else {
      alphabet.push_back(c);
    }
  }
  std::sort(alphabet.begin(), alphabet.end());

  // build tree
  this->root = build2(str, 0, str.size()-1, alphabet);
}

int WaveletTree::rank(char q, int x) {
    return 0;
}

int WaveletTree::select(char q, int x) {
    return 0;
}

char WaveletTree::access(int x) {
    return 0;
}
