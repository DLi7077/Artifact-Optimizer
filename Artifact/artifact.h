#pragma once
#include "../Constants/utils.h"
#include "./stat.h"

class Artifact {
 public:
  // two-param constructor
  Artifact(const std::array<std::string, SUBSTAT_COUNT>& substats, std::string mainStat) {
    main_stat_ = Stat(mainStat);
    main_stat_.setMainStat();

    substats_ = new Stat*[SUBSTAT_COUNT];
    
    for (size_t i = 0; i < SUBSTAT_COUNT; i++) {
      substats_[i] = new Stat(substats[i]);
    }
  }

  // copy constructor
  Artifact(const Artifact& rhs) {
    main_stat_ = Stat(rhs.main_stat_);
    substats_ = new Stat*[SUBSTAT_COUNT];

    for (size_t i = 0; i < SUBSTAT_COUNT; i++) {
      substats_[i] = rhs.substats_[i];  // only possible due to copy assignment
    }
  }

  // move constructor
  Artifact(Artifact&& rhs) {
    main_stat_ = Stat(rhs.main_stat_);
    substats_ = new Stat*[SUBSTAT_COUNT];

    for (size_t i = 0; i < SUBSTAT_COUNT; i++) {
      substats_[i] = rhs.substats_[i];
    }

    rhs.substats_ = nullptr;
  }

  // move assignment
  Artifact& operator=(Artifact&& rhs) {
    std::swap(main_stat_, rhs.main_stat_);
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

    return *substats_[location];
  }

  friend std::ostream& operator<<(std::ostream& out, const Artifact& rhs) {
    out << "main:\t" << rhs.main_stat_;
    for (int i = 0; i < SUBSTAT_COUNT; i++) {
      out << *rhs.substats_[i];
    }
    out << "\n";
    return out;
  }

 private:
  Stat** substats_;
  Stat main_stat_;
};