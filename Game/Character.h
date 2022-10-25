#pragma once
#include "../Constants/utils.h"
#include "./Artifact/artifact.h"

class Character {
 private:
  std::unordered_map<std::string, double> stats_;
  std::unordered_map<std::string, double> damage_bonus_;

  void InitCharacterStats() {
    stats_[BASE_ATTACK] = 0;
    stats_[BASE_HP] = 0;
    stats_[BASE_DEFENSE] = 0;
    stats_[ATTACK_PERCENT] = 0;
    stats_[HP_PERCENT] = 0;
    stats_[DEFENSE_PERCENT] = 0;
    stats_[FLAT_ATTACK] = 0;
    stats_[FlAT_HP] = 0;
    stats_[FLAT_DEFENSE] = 0;
    stats_[ELEMENTAL_MASTERY] = 15;
    stats_[ENERGY_RECHARGE] = 50;
    stats_[CRIT_RATE] = 0;
    stats_[CRIT_DAMAGE] = 0;
  }

  void InitCharacterDamageBonus() {
    damage_bonus_[ANEMO];
    damage_bonus_[CRYO];
    damage_bonus_[DENDRO];
    damage_bonus_[ELECTRO];
    damage_bonus_[HYDRO];
    damage_bonus_[PYRO];
    damage_bonus_[PHYSICAL];
  }

 public:
  Character() {
    InitCharacterStats();
    InitCharacterDamageBonus();
  }

  // Sets one 
  void setStat(){

  }
};