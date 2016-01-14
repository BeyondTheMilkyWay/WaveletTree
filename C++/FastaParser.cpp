//
// Created by Domagoj Stankovic on 1/14/16.
//

#include "FastaParser.h"
#include <fstream>

std::string FastaParser::parse(std::string &filePath) {
  std::string str;
  std::ifstream infile(filePath);
  std::string line;
  while (std::getline(infile, line)) {
    if (line[0] == '>') continue; // header
    str.append(line);
  }
  return str;
}
