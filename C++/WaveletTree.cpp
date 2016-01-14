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

WaveletNodeP build_by_copy_sort(std::string &str, int l, int r, std::vector<char> &alphabet) {
  if (alphabet.size() <= 1) {
    return std::make_shared<WaveletNodeNull>(alphabet);
  }
  int size = r - l + 1;

  // build bitstring, 0-string and 1-string
  std::unique_ptr<std::string> str0(new std::string);
  std::unique_ptr<std::string> str1(new std::string);
  BitArray bitArray(size);
  std::map<char, bool> map;
  for (int i = 0; i < size; i++) {
    char c = str[i + l];
    bool cd = code(map, alphabet, c);
    bitArray.set(i, cd);
    if (cd) {
      str1->push_back(c);
    } else {
      str0->push_back(c);
    }
  }

  unsigned long str0size = str0->size();
  for (unsigned long i = 0; i < str0size; i++) {
    str[i + l] = (*str0)[i];
  }
  unsigned long str1size = str1->size();
  for (unsigned long i = 0; i < str1size; i++) {
    str[i + l + str0size] = (*str1)[i];
  }
  str0 = NULL;
  str1 = NULL;

  int mid = l + str0size;
  std::vector<char> lAlphabet(alphabet.begin(), alphabet.begin() + alphabet.size() / 2);
  WaveletNodeP left = build_by_copy_sort(str, l, mid - 1, lAlphabet);
  std::vector<char> rAlphabet(alphabet.begin() + alphabet.size() / 2, alphabet.end());
  WaveletNodeP right = build_by_copy_sort(str, mid, r, rAlphabet);
  std::shared_ptr<WaveletNode> node = std::make_shared<WaveletNode>(bitArray, alphabet, left, right);
  left->parent = node;
  right->parent = node;
  return node;
}

WaveletNodeP build_by_copy(std::string &str, std::vector<char> &alphabet) {
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
  WaveletNodeP left = build_by_copy(str0, lAlphabet);
  std::vector<char> rAlphabet(alphabet.begin() + alphabet.size() / 2, alphabet.end());
  WaveletNodeP right = build_by_copy(str1, rAlphabet);
  std::shared_ptr<WaveletNode> node = std::make_shared<WaveletNode>(bitArray, alphabet, left, right);
  left->parent = node;
  right->parent = node;
  return node;
}

void convertString(std::string &str) {
  for (int i = str.size() - 1; i >= 0; i--) {
    if (str[i] == ' ') {
      str[i] = '_';
    }
  }
  str.push_back('$');
}

void WaveletTree::build(std::string &str) {
  // extract and sort alphabet
  convertString(str);
  std::set<char> chars;
  for (char c : str) {
    chars.insert(c);
  }
  std::vector<char> alphabet;
  for (char c : chars) {
    alphabet.push_back(c);
  }
  std::sort(alphabet.begin(), alphabet.end());

  // build tree
  this->root = build_by_copy(str, alphabet);
//  this->root = build_by_sort(str, 0, str.size()-1, alphabet);
  this->root->setRoot(true);
}

int WaveletTree::rank(char q, int x) {
  WaveletNodeP node = root;
  int rank = x;
  while (!node->isNull()) {
    bool b = node->bitcode(q);
    rank = node->binary_rank(b, rank);
    node = b ? node->right : node->left;
  }
  return rank;
}

int WaveletTree::select(char q, int x) {
  // go down
  WaveletNodeP node = root;
  while (!node->isNull()) {
    bool b = node->bitcode(q);
    node = b ? node->right : node->left;
  }

  // go up
  int i = x;
  while (!node->isRoot()) {
    auto parent = node->parent.lock();
    bool b = parent->bitcode(q);
    i = parent->binary_select(b, i);
    if (i < 0) {
      return -1;
    }
    node = parent;
  }
  return i;
}

char WaveletTree::access(int x) {
  auto node = this->root;
  int pos = x;
  while (!node->isNull()) {
    if (pos >= node->bitArray.size()) {
      return '?';
    }
    bool b = node->bitArray.get(pos);
    int rank = node->binary_rank(b, pos+1);
    pos = rank - 1;
    node = b ? node->right : node->left;
  }
  return node->alphabet[0];
}
