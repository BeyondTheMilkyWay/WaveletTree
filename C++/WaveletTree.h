//
// Created by Domagoj Stankovic on 1/11/16.
//

#ifndef WAVELETTREE_WAVELETTREE_H
#define WAVELETTREE_WAVELETTREE_H


#include <memory>
#include "WaveletNode.h"

/**
 * Class representing Wavelet tree.
 * It contains only root node.
 * String is 0-indexed.
 */
class WaveletTree {
public:
    WaveletTree(std::string &str) {
      build(str);
    }

    int rank(char q, int x); // returns the number of elements equal to q up to position x
    int select(char q, int x); // returns the position of the x-th occurrence of q
    char access(int x); // character on x-th position in a string

    const WaveletNodeP &getRoot() const {
      return root;
    }

    unsigned long __sizeof();

private:
    WaveletNodeP root;
    void build(std::string &str); // builds the tree from given string
};


#endif //WAVELETTREE_WAVELETTREE_H
