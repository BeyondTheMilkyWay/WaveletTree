//
// Created by Domagoj Stankovic on 1/11/16.
//

#include "WaveletNode.h"

int WaveletNode::binary_rank(bool q, int x) {
  int sum = 0;
  for (std::size_t i = 0; i <= x; i++) {
    sum += this->bitset.test(i) ^ q ? 0 : 1;
  }
  return sum;
}


static bool WaveletNode::bitcode(std::vector<char> alphabet, char q) {
  int pos = std::find(alphabet.begin(), alphabet.end(), q) - alphabet.begin();
  unsigned long size = alphabet.size();
  return pos >= size / 2;
}
