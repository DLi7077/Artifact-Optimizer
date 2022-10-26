#pragma once
#include "../Constants/constants.h"
#include "../Constants/utils.h"

class Enemy {
 private:
  int level;
  std::unordered_map<std::string, double> resistance_percent_;

 public:
  Enemy() {
    resistance_percent_[ANEMO] = .10;
    resistance_percent_[CRYO] = .10;
    resistance_percent_[DENDRO] = .10;
    resistance_percent_[ELECTRO] = .10;
    resistance_percent_[HYDRO] = .10;
    resistance_percent_[PYRO] = .10;
    resistance_percent_[PHYSICAL] = .10;
  }

  ~Enemy() {
    resistance_percent_.clear();
  }

  void setResistance(std::string element, double value) {
    if (!(Constants::validateElement(element))) {
      std::cerr << "\"" << element << "\" is not a valid element type.\n";
      abort();
    }
    resistance_percent_[element] = value;
  }

  double getResistance(std::string element) {
    if (!(Constants::validateElement(element))) {
      std::cerr << "\"" << element << "\" is not a valid element type.\n";
      abort();
    }
    return resistance_percent_[element];
  }
};
