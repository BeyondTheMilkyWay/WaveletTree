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


bool WaveletNode::bitcode(char q) {
  int pos = std::find(this->alphabet.begin(), this->alphabet.end(), q) - this->alphabet.begin();
  unsigned long size = this->alphabet.size();
  return pos >= size / 2;
}
