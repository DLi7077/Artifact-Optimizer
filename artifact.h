#pragma once
#include "./stat.h"
#include "./utils.h"

class Artifact {
 public:
  // one-param constructor
  Artifact(const std::array<std::string, SUBSTAT_COUNT>& rhs) {
    substats_ = new Stat[SUBSTAT_COUNT];
    for (size_t i = 0; i < SUBSTAT_COUNT; i++) {
      substats_[i] = Stat(rhs[i]);
    }
  }

  // copy constructor
  Artifact(const Artifact& rhs) {
    substats_ = new Stat[SUBSTAT_COUNT];

    for (size_t i = 0; i < SUBSTAT_COUNT; i++) {
      substats_[i] = rhs.substats_[i];  // only possible due to copy assignment
    }
  }

  // move constructor
  Artifact(Artifact&& rhs) {
    std::cout << "movec";
    substats_ = new Stat[SUBSTAT_COUNT];

    for (size_t i = 0; i < SUBSTAT_COUNT; i++) {
      substats_[i] = rhs.substats_[i];
    }

    rhs.substats_ = nullptr;
  }

  // move assignment
  Artifact& operator=(Artifact&& rhs) {
    std::cout << "movea";

    std::swap(substats_, rhs.substats_);

    return *this;
  }

  ~Artifact() {
    if (substats_) {
      delete substats_;
      substats_ = nullptr;
    }
  }

  int size() const {
    return SUBSTAT_COUNT;
  }

  Stat& operator[](size_t location) {
    if (location < 0 || location > SUBSTAT_COUNT) {
      std::cerr << "index " << location << " Out of Bounds";
      abort();
    }

    return substats_[location];
  }

  friend std::ostream& operator<<(std::ostream& out, const Artifact& rhs) {
    for (int i = 0; i < SUBSTAT_COUNT; i++) {
      out << rhs.substats_[i];
    }
    out << "\n";
    return out;
  }

 private:
  Stat* substats_;
};