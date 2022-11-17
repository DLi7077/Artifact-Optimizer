#pragma once
#include "../../Constants/pch.h"

namespace Attributes {
// support for stats like Hu Tao E and 4pc emblem of severed fate
class BonusStatGain {
 public:
  std::string source_stat_;  // stat that bonus is proportional to
  std::string target_stat_;  // target stat to buff
  double source_offset_;     // threshold to gain bonus (4pc emblem = min(0.75, (ER-100) * .25))
  double percent_gain_;      // percentage gain
  double max_gain_;          // maximum gain

  // constructor
  BonusStatGain(
      std::string sourceStat,
      std::string targetStat,
      double sourceOffset,
      double percentGain,
      double maxGain) {
    source_stat_ = sourceStat;
    target_stat_ = targetStat;
    source_offset_ = sourceOffset;
    percent_gain_ = percentGain;
    max_gain_ = maxGain;
  }

  // // copy constructor
  // BonusStatGain(const BonusStatGain &rhs) {
  //   source_stat_ = rhs.source_stat_;
  //   target_stat_ = rhs.target_stat_;
  //   percent_gain_ = rhs.percent_gain_;
  //   max_gain_ = rhs.max_gain_;
  // }

  // // copy assignment
  // BonusStatGain operator=(const BonusStatGain &rhs) {
  //   BonusStatGain copy = rhs;
  //   std::swap(*this, copy);

  //   return *this;
  // }

  // // move constructor
  // BonusStatGain(BonusStatGain &&rhs) {
  //   source_stat_ = rhs.source_stat_;
  //   target_stat_ = rhs.target_stat_;
  //   percent_gain_ = rhs.percent_gain_;
  //   max_gain_ = rhs.max_gain_;
  // }
};

}  // namespace Attributes