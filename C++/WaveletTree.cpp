//
// Created by Domagoj Stankovic on 1/11/16.
//

#include <set>
#include <map>
#include "WaveletTree.h"

static bool code(std::map<char, bool> &map, std::vector<char> &alphabet, char q) {
  if (map.find(q) == map.end()) {
    // key doesn't exist
    map[q] = WaveletNode::bitcode(alphabet, q);
  }
  return map[q];
}

static WaveletNodeP build(std::string &str, int l, int r, std::vector<char> &alphabet) {
  if (alphabet.size() <= 1) {
    return NULL;
  }
  std::bitset<r - l + 1> bitset;
  std::map<char, bool> map;
  for (int i = l; i <= r; i++) {
    bitset[i - l] = code(map, alphabet, str[i]);
  }
  std::vector<char> lAlphabet(alphabet.begin(), alphabet.begin() + alphabet.size() / 2);
  WaveletNodeP left = build(str, l, (l + r)/2, lAlphabet);
  std::vector<char> rAlphabet(alphabet.begin() + alphabet.size() / 2, alphabet.end());
  WaveletNodeP right = build(str, (l + r)/2 + 1, r, rAlphabet);
  WaveletNodeP node = new WaveletNode(bitset, alphabet, left, right);
  if (left != NULL) left->parent = node;
  if (right != NULL) right->parent = node;
  return node;
}

void WaveletTree::build(std::string &str) {
  // extract and sort alphabet
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
  this->root = build(str, 0, alphabet.size()-1, alphabet);
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
