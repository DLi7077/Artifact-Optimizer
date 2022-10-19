#pragma once
#include "./constants.h"
#include "./utils.h"

class Stat {
 public:
  // default
  Stat() {
    label_ = "";
    value_ = 0;
  }

  // one-param
  Stat(std::string label) {
    label_ = label;
    value_ = Constants::getMaxRollMapping()[label];
  }

  // copy constructor
  Stat(const Stat& rhs) {
    label_ = rhs.label_;
    value_ = rhs.value_;
  }

  // copy assignment
  Stat& operator=(const Stat& rhs) {
    Stat tempCopy = rhs;
    std::swap(*this, tempCopy);

    return *this;
  }

  // move constructor
  Stat(Stat&& rhs) {
    label_ = rhs.label_;
    value_ = rhs.value_;

    rhs.label_ = "";
    rhs.value_ = 0;
  }

  // move assignment
  Stat& operator=(Stat&& rhs) {
    std::swap(label_, rhs.label_);
    std::swap(value_, rhs.value_);

    return *this;
  }

  ~Stat() {
    label_ = "";
    value_ = 0;
  }

  friend std::ostream& operator<<(std::ostream& out, const Stat& rhs) {
    std::cout << rhs.label_ << " " << rhs.value_ << "\n";
    return out;
  }

  // simulate roll
  void operator+=(int rolls) {
    double value = Constants::getMaxRollMapping()[this->label_];
    this->value_ += rolls * value;
    return;
  }

 private:
  std::string label_;
  double value_;
};