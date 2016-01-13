//
// Created by Domagoj Stankovic on 1/11/16.
//

#include "WaveletNode.h"

int WaveletNode::binary_rank(bool q, int x) {
  int sum = 0;
  for (std::size_t i = 0; i < x; i++) {
    sum += this->bitArray.get(i) ^ q ? 0 : 1;
  }
  return sum;
}


int WaveletNode::binary_select(bool q, int x) {
  int cnt = x + 1;
  int index = 0;
  while (cnt > 0) {
    bool val = bitArray.get(index);
    if (q == val) {
      cnt--;
    }
    index++;
  }
  return index - 1;
}
