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
    std::shared_ptr<WaveletNode> root;
    void build();
};


#endif //WAVELETTREE_WAVELETTREE_H
