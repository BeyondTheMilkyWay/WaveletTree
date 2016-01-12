//
// Created by Domagoj Stankovic on 1/11/16.
//

#ifndef WAVELETTREE_WAVELETTREE_H
#define WAVELETTREE_WAVELETTREE_H


#include <memory>
#include "WaveletNode.h"

class WaveletTree {
public:
    int rank(char q, int x);
    int select(char q, int x);
    char access(int x);

private:
    WaveletNodeP root;
    void build(std::string &str);
};


#endif //WAVELETTREE_WAVELETTREE_H
