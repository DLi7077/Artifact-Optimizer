#pragma once
#include "../Constants/utils.h"
#include "./Artifact/artifact.h"

class Character {
 public:
  Character() {}

  // base stats
  void setBaseAttack(double base_attack) {
    base_attack_ = base_attack;
  }
  void setBaseDefense(double base_defense) {
    base_defense_ = base_defense;
  }
  void setBaseHP(double base_hp) {
    base_HP_ = base_hp;
  }

  // percent stats
  void setAttackPercent(double attack_percent) {
    attack_percent_ = attack_percent;
  }
  void setHPPercent(double hp_percent) {
    hp_percent_ = hp_percent;
  }
  void setDefensePercent(double defense_percent) {
    defense_percent_ = defense_percent;
  }

  // flat stats
  void setFlatAttack(double flat_attack) {
    flat_attack_ = flat_attack;
  }
  void setFlatHP(double flat_hp) {
    flat_hp_ = flat_hp;
  }
  void setFlatDefense(double flat_defense) {
    flat_defense_ = flat_defense;
  }

  // bonus multipliers
  void setCritRate(double crit_rate) {
    crit_rate_percent_ = crit_rate;
  }
  void setCritRate(double crit_damage_percent) {
    crit_damage_percent_ = crit_damage_percent;
  }
  void setElementalDMG(double elemental_damage_bonus) {
    elemental_damage_bonus_ = elemental_damage_bonus;
  }

  // other
  void setElementalMastery(double elemental_mastery) {
    elemental_mastery_ = elemental_mastery;
  }
  void setEnergyRecharge(double energy_recharge) {
    enery_recharge_ = energy_recharge;
  }
  void setDefensePenetration(double defense_penetration_percent) {
    defense_penetration_percent_ = defense_penetration_percent;
  }

 private:
  double base_attack_;
  double base_HP_;
  double base_defense_;
  double attack_percent_;
  double hp_percent_;
  double defense_percent_;
  double flat_attack_;
  double flat_hp_;
  double flat_defense_;
  double crit_rate_percent_ = 15;
  double crit_damage_percent_ = 50;
  double elemental_damage_bonus_;
  double elemental_mastery_;
  double enery_recharge_ = 100;
  double defense_penetration_percent_;
};