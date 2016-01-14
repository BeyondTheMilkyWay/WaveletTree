//
// Created by Domagoj Stankovic on 1/12/16.
//

#ifndef WAVELETTREE_BITARRAY_H
#define WAVELETTREE_BITARRAY_H


#include <vector>
#include <string>

/**
 * Class representing array of bits even though underlying implementation
 * uses vector of chars.
 */
class BitArray {
private:
    std::vector<char> arr;
public:

    // Size of bit array
    BitArray(int size) {
      for (int i = 0; i < size; i++) {
        arr.push_back(0);
      }
    }

    bool get(int i);
    void set(int i, char value);
    int size();

    std::string toString();

    unsigned long __sizeof();
};


#endif //WAVELETTREE_BITARRAY_H
