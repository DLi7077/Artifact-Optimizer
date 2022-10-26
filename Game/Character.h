#pragma once
#include "../Artifact/artifact.h"
#include "../Constants/constants.h"
#include "../Constants/utils.h"

#define SKILL_DAMAGE_SCALING "Skill Damage %"
#define BURST_DAMAGE_SCALING "Burst Damage %"

#define DEFAULT_BASE_ATK 800
#define DEFAULT_BASE_HP 10000
#define DEFAULT_BASE_DEF 200

struct StatModel {
  double total_attack;
  double total_hp;
  double total_defense;
  double elemental_mastery;
  double energy_recharge;
  double crit_rate;
  double crit_damage;
  double damage_bonus_anemo;
  double damage_bonus_cryo;
  double damage_bonus_dendro;
  double damage_bonus_electro;
  double damage_bonus_hydro;
  double damage_bonus_pyro;
  double damage_bonus_physical;
};

class Character {
 private:
  std::unordered_map<std::string, double> stats_;
  std::unordered_map<std::string, double> damage_bonus_;
  std::unordered_map<std::string, double> talent_scaling_;
  StatModel final_stats_;

  void InitCharacterStats() {
    stats_[BASE_ATK] = DEFAULT_BASE_ATK;
    stats_[BASE_HP] = DEFAULT_BASE_HP;
    stats_[BASE_DEFENSE] = DEFAULT_BASE_DEF;
    stats_[ATK_PERCENT] = 0;
    stats_[HP_PERCENT] = 0;
    stats_[DEF_PERCENT] = 0;
    stats_[FLAT_ATK] = 0;
    stats_[FLAT_HP] = 0;
    stats_[FLAT_DEF] = 0;
    stats_[ELEMENTAL_MASTERY] = 0;
    stats_[ENERGY_RECHARGE] = 1;
    stats_[CRIT_RATE] = .05;
    stats_[CRIT_DAMAGE] = .5;
  }

  void InitCharacterDamageBonus() {
    damage_bonus_[ANEMO] = 0;
    damage_bonus_[CRYO] = 0;
    damage_bonus_[DENDRO] = 0;
    damage_bonus_[ELECTRO] = 0;
    damage_bonus_[HYDRO] = 0;
    damage_bonus_[PYRO] = 0;
    damage_bonus_[PHYSICAL] = 0;
  }

  void InitCharacterTalentScaling() {
    talent_scaling_[SKILL_DAMAGE_SCALING] = 1.00;
    talent_scaling_[BURST_DAMAGE_SCALING] = 3.027;
  }

  void updateStatModel() {
    final_stats_.total_attack = stats_[BASE_ATK] * (1 + stats_[ATK_PERCENT]) + stats_[FLAT_ATK];
    final_stats_.total_hp = stats_[BASE_HP] * (1 + stats_[HP_PERCENT]) + stats_[FLAT_HP];
    final_stats_.total_defense = stats_[BASE_DEFENSE] * (1 + stats_[DEF_PERCENT]) + stats_[FLAT_DEF];
    final_stats_.elemental_mastery = stats_[ELEMENTAL_MASTERY];
    final_stats_.energy_recharge = stats_[ENERGY_RECHARGE];
    final_stats_.crit_rate = stats_[CRIT_RATE];
    final_stats_.crit_damage = stats_[CRIT_DAMAGE];
    final_stats_.damage_bonus_anemo = damage_bonus_[ANEMO];
    final_stats_.damage_bonus_cryo = damage_bonus_[CRYO];
    final_stats_.damage_bonus_dendro = damage_bonus_[DENDRO];
    final_stats_.damage_bonus_electro = damage_bonus_[ELECTRO];
    final_stats_.damage_bonus_hydro = damage_bonus_[HYDRO];
    final_stats_.damage_bonus_pyro = damage_bonus_[PYRO];
    final_stats_.damage_bonus_physical = damage_bonus_[PHYSICAL];
  }

  bool isDmgBonus(std::string& label) {
    if (label == ANEMO_DAMAGE_BONUS) return true;
    if (label == CRYO_DAMAGE_BONUS) return true;
    if (label == DENDRO_DAMAGE_BONUS) return true;
    if (label == ELECTRO_DAMAGE_BONUS) return true;
    if (label == HYDRO_DAMAGE_BONUS) return true;
    if (label == PYRO_DAMAGE_BONUS) return true;
    if (label == PHYSICAL_DAMAGE_BONUS) return true;

    return false;
  }

  std::string labelCastToElement(std::string& label) {
    if (label == ANEMO_DAMAGE_BONUS) return ANEMO;
    if (label == CRYO_DAMAGE_BONUS) return CRYO;
    if (label == DENDRO_DAMAGE_BONUS) return DENDRO;
    if (label == ELECTRO_DAMAGE_BONUS) return ELECTRO;
    if (label == HYDRO_DAMAGE_BONUS) return HYDRO;
    if (label == PYRO_DAMAGE_BONUS) return PYRO;
    if (label == PHYSICAL_DAMAGE_BONUS) return PHYSICAL;

    return label;
  }

 public:
  Character() {
    InitCharacterStats();
    InitCharacterDamageBonus();
    updateStatModel();
  }
  ~Character() {
    stats_.clear();
    damage_bonus_.clear();
  }

  // accessors and mutators
  double getStat(std::string label) {
    return stats_[label];
  }
  double getDamageBonus(std::string label) {
    return damage_bonus_[label];
  }
  void setStat(std::string label, double value) {
    stats_[label] = value;
    updateStatModel();
  }
  void setDamageBonus(std::string label, double value) {
    stats_[label] = value;
    updateStatModel();
  }

  const StatModel& finalStats() {
    return final_stats_;
  }

  void addArtifact(Artifact& artifact) {
    Stat mainStat = artifact.mainStat();
    std::string mainLabel = mainStat.label();
    std::unordered_map<std::string, double>& stats = isDmgBonus(mainLabel) ? damage_bonus_ : stats_;
    mainLabel = labelCastToElement(mainStat.label());

    stats[mainLabel] += mainStat.value();

    for (size_t i = 0; i < artifact.size(); i++) {
      std::string statLabel = artifact[i].label();
      stats[statLabel] += artifact[i].value();
    }

    updateStatModel();
  }

  friend std::ostream& operator<<(std::ostream& out, Character& rhs) {
    out << "Base FLAT_ATK:\t\t" << rhs.stats_[BASE_ATK] << "\n";
    out << "ATK\t\t\t" << rhs.final_stats_.total_attack << "\n";
    out << "MAX HP:\t\t\t" << rhs.final_stats_.total_hp << "\n";
    out << "DEF:\t\t\t" << rhs.final_stats_.total_defense << "\n";
    out << "Elemental Mastery:\t" << rhs.final_stats_.elemental_mastery << "\n";
    out << "Energy Recharge:\t" << rhs.final_stats_.energy_recharge * 100 << "%\n";
    out << "Crit Rate:\t\t" << rhs.final_stats_.crit_rate * 100 << "%\n";
    out << "Crit Damage:\t\t" << rhs.final_stats_.crit_damage * 100 << "%\n";
    out << "Anemo DMG Bonus:\t" << rhs.final_stats_.damage_bonus_anemo * 100 << "%\n";
    out << "Cryo DMG Bonus: \t" << rhs.final_stats_.damage_bonus_cryo * 100 << "%\n";
    out << "Dendro DMG Bonus:\t" << rhs.final_stats_.damage_bonus_dendro * 100 << "%\n";
    out << "Electro DMG Bonus:\t" << rhs.final_stats_.damage_bonus_electro * 100 << "%\n";
    out << "Hydro DMG Bonus:\t" << rhs.final_stats_.damage_bonus_hydro * 100 << "%\n";
    out << "Pyro DMG Bonus: \t" << rhs.final_stats_.damage_bonus_pyro * 100 << "%\n";
    out << "Physical DMG Bonus:\t" << rhs.final_stats_.damage_bonus_physical * 100 << "%\n";

    return out;
  }

  // damage calculation

  double meltVapeBonus(double EM) {
    return 2.78 * (EM / 1400);
  }
};