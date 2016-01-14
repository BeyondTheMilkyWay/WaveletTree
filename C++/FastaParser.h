//
// Created by Domagoj Stankovic on 1/14/16.
//

#ifndef WAVELETTREE_FASTAPARSER_H
#define WAVELETTREE_FASTAPARSER_H

#include <iostream>

/**
 * Parser for files in FASTA format.
 */
class FastaParser {
public:
    /**
     * Parses FASTA file. First line (with '>') is ignored.
     */
    std::string parse(std::string &filePath);
};


#endif //WAVELETTREE_FASTAPARSER_H
