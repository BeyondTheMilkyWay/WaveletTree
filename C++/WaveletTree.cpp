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

WaveletNodeP build2(std::string &str, std::vector<char> &alphabet) {
  if (alphabet.size() <= 1) {
    return std::make_shared<WaveletNodeNull>(alphabet);
  }
  int size = str.size();

  // build bitstring, 0-string and 1-string
  std::string str0;
  std::string str1;
  BitArray bitArray(size);
  std::map<char, bool> map;
  for (int i = 0; i < size; i++) {
    bool cd = code(map, alphabet, str[i]);
    bitArray.set(i, cd);
    if (cd) {
      str1.push_back(str[i]);
    } else {
      str0.push_back(str[i]);
    }
  }

  std::vector<char> lAlphabet(alphabet.begin(), alphabet.begin() + alphabet.size() / 2);
  WaveletNodeP left = build2(str0, lAlphabet);
  std::vector<char> rAlphabet(alphabet.begin() + alphabet.size() / 2, alphabet.end());
  WaveletNodeP right = build2(str1, rAlphabet);
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
  this->root = build2(str, alphabet);
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
