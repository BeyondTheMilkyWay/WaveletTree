//
// Created by Domagoj Stankovic on 1/12/16.
//

#ifndef WAVELETTREE_WAVELETNODENULL_H
#define WAVELETTREE_WAVELETNODENULL_H


#include "WaveletNode.h"

class WaveletNodeNull : public WaveletNode {

public:
    WaveletNodeNull(std::vector<char> &alphabet) : WaveletNode(*(new BitArray(0)), alphabet, NULL, NULL) { }
    virtual bool isNull() override;
};


#endif //WAVELETTREE_WAVELETNODENULL_H
