#pragma once
#include "../Constants/constants.h"
#include "../Constants/pch.h"

#define DEFAULT_ENEMY_LEVEL 93
#define DEFAULT_AFFECTED_ELEMENT PYRO

class Enemy {
 private:
  int enemy_level_;
  std::unordered_map<std::string, double> resistance_percent_;
  std::string affected_element_ = DEFAULT_AFFECTED_ELEMENT;

 public:
  Enemy() {
    enemy_level_ = DEFAULT_ENEMY_LEVEL;
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

  int getLevel() {
    return enemy_level_;
  }

  double getResistance(std::string element) {
    if (!(Constants::validateElement(element))) {
      std::cerr << "\"" << element << "\" is not a valid element type.\n";
      abort();
    }
    return resistance_percent_[element];
  }

  std::string getAffectedElement() {
    return affected_element_;
  }

  void setLevel(int level) {
    enemy_level_ = level;
  }
  void setResistance(std::string element, double value) {
    if (!(Constants::validateElement(element))) {
      std::cerr << "\"" << element << "\" is not a valid element type.\n";
      abort();
    }
    resistance_percent_[element] = value;
  }
  void setAffectedElement(std::string element) {
    affected_element_ = element;
  }
};
