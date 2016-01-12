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
