//
// Created by Domagoj Stankovic on 1/12/16.
//

#ifndef WAVELETTREE_BITARRAY_H
#define WAVELETTREE_BITARRAY_H


#include <vector>
#include <string>

class BitArray {
private:
    std::vector<char> arr;
public:

    BitArray(int size) {
      for (int i = 0; i < size; i++) {
        arr.push_back(0);
      }
    }

    bool get(int i);
    void set(int i, char value);

    std::string toString();
};


#endif //WAVELETTREE_BITARRAY_H
