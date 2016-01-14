//
// Created by Domagoj Stankovic on 1/11/16.
//

#ifndef WAVELETTREE_WAVELETNODE_H
#define WAVELETTREE_WAVELETNODE_H


#include <vector>
#include <bitset>
#include "BitArray.h"
#include "NullableObject.h"

class WaveletNode : public NullableObject {
public:
    BitArray bitArray;
    std::vector<char> alphabet;
    std::weak_ptr<WaveletNode> parent;
    std::shared_ptr<WaveletNode> left;
    std::shared_ptr<WaveletNode> right;

    WaveletNode(const BitArray bitArray, const std::vector<char> &alphabet, const std::shared_ptr<WaveletNode> &left,
                const std::shared_ptr<WaveletNode> &right) : bitArray(bitArray), alphabet(alphabet), left(left),
                                                             right(right) { }

    int binary_rank(bool q, int x); // binary rank [0, x>
    int binary_select(bool q, int x); // binary select [0, x]

    // code for q in alphabet for this node
    static bool bitcode(std::vector<char> alphabet, char q) {
      int pos = (int) (std::find(alphabet.begin(), alphabet.end(), q) - alphabet.begin());
      unsigned long size = alphabet.size();
      return pos >= size / 2;
    }

    bool bitcode(char q) {
      return WaveletNode::bitcode(this->alphabet, q);
    }

    bool isRoot() const {
      return _root;
    }

    void setRoot(bool root) {
      WaveletNode::_root = root;
    }

private:
    bool _root = false;
};

typedef std::shared_ptr<WaveletNode> WaveletNodeP;

#endif //WAVELETTREE_WAVELETNODE_H
