//
// Created by Jeremy Novak on 9/29/24.
//

#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>

class WordCounter {
 public:
  static size_t countWords(const std::string &line) {
      std::istringstream iss(line);
      return std::distance(std::istream_iterator<std::string>(iss),
                           std::istream_iterator<std::string>());
  }
};
