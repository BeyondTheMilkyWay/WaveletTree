//
// Created by Domagoj Stankovic on 1/11/16.
//

#ifndef WAVELETTREE_WAVELETNODE_H
#define WAVELETTREE_WAVELETNODE_H


#include <vector>
#include <bitset>

template <int bits>
class WaveletNode {
public:
    std::bitset<bits> bitset;
    std::vector<char> alphabet;
    std::weak_ptr<WaveletNode> parent;
    std::shared_ptr<WaveletNode> left;
    std::shared_ptr<WaveletNode> right;

    WaveletNode(const std::bitset<bits> &bitset, const std::vector<char> &alphabet,
                const std::shared_ptr<WaveletNode> &left, const std::shared_ptr<WaveletNode> &right) : bitset(
            bitset), alphabet(alphabet), left(left), right(right) { }

    int binary_rank(bool q, int x); // binary rank [0, x]

    static bool bitcode(std::vector<char> alphabet, char q); // code for q in alphabet for this node
};

template <int bits>
using WaveletNodeP<bits> = std::shared_ptr<WaveletNode<bits>>;

#endif //WAVELETTREE_WAVELETNODE_H
