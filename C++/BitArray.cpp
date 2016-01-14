//
// Created by Domagoj Stankovic on 1/12/16.
//

#include "BitArray.h"

bool BitArray::get(int i) {
  return arr[i] == 1;
}


void BitArray::set(int i, char value) {
  arr[i] = value;
}

std::string BitArray::toString() {
  std::string str("");
  for (char c : arr) {
    str.push_back(c+'0');
  }
  return str;
}

int BitArray::size() {
  return arr.size();
}

unsigned long BitArray::__sizeof() {
  return arr.capacity() * sizeof(char);
}
