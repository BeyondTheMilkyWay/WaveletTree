//
// Created by Domagoj Stankovic on 1/11/16.
//

#ifndef WAVELETTREE_WAVELETNODE_H
#define WAVELETTREE_WAVELETNODE_H


#include <vector>
#include <bitset>

typedef std::shared_ptr<WaveletNode> WaveletNodeP;

template <int bits>
class WaveletNode {
public:
    WaveletNode(const std::bitset<bits> &bitset, const std::vector<char> &alphabet,
                const std::weak_ptr<WaveletNode> &parent, const WaveletNodeP &left, const WaveletNodeP &right) : bitset(
            bitset), alphabet(alphabet), parent(parent), left(left), right(right) { }

    int binary_rank(bool q, int x); // binary rank [0, x]
private:
    std::bitset<bits> bitset;
    std::vector<char> alphabet;
    std::weak_ptr<WaveletNode> parent;
    WaveletNodeP left;
    WaveletNodeP right;

    bool bitcode(char q); // code for q in alphabet for this node
};


#endif //WAVELETTREE_WAVELETNODE_H
