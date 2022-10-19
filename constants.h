#pragma once
#include "./utils.h"

#define ATK "ATK"
#define ATK_PERCENT "ATK%"
#define HP "HP"
#define HP_PERCENT "HP%"
#define DEF "DEF"
#define DEF_PERCENT "DEF%"
#define ELEMENTAL_MASTERY "EM"
#define ENERGY_RECHARGE "ER%"
#define CRIT_RATE "Crit Rate%"
#define CRIT_DAMAGE "Crit Dmg%"

#define MAX_ATK_ROLL 19.45
#define MAX_ATK_PERCENT_ROLL 5.84
#define MAX_HP_ROLL 0
#define MAX_HP_PERCENT_ROLL 0
#define MAX_DEF_ROLL 0
#define MAX_DEF_PERCENT_ROLL 0
#define MAX_EM_ROLL 23.31
#define MAX_ER_PERCENT_ROLL 6.48
#define MAX_CRIT_RATE_ROLL 3.87
#define MAX_CRIT_DAMAGE_ROLL 7.77

class Constants {
 public:
  static std::unordered_map<std::string, double>& getMaxRollMapping() {
    return max_roll_mapping_;
  }

 private:
  inline static std::unordered_map<std::string, double> max_roll_mapping_ = {
      {ATK, MAX_ATK_ROLL},
      {ATK_PERCENT, MAX_ATK_PERCENT_ROLL},
      {HP, MAX_HP_ROLL},
      {HP_PERCENT, MAX_HP_PERCENT_ROLL},
      {DEF, MAX_DEF_ROLL},
      {DEF_PERCENT, MAX_DEF_PERCENT_ROLL},
      {ELEMENTAL_MASTERY, MAX_EM_ROLL},
      {ENERGY_RECHARGE, MAX_ER_PERCENT_ROLL},
      {CRIT_RATE, MAX_CRIT_RATE_ROLL},
      {CRIT_DAMAGE, MAX_CRIT_DAMAGE_ROLL}};
};
