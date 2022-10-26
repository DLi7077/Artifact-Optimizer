#include "../Constants/constants.h"
#include "../Constants/utils.h"
#include "./Character.h"
#include "./Enemy.h"

struct DamageOutput {
  double skill_damage;
  double burst_damage;
};

namespace Calculator {
/*
(BASE_DAMAGE + BONUS_BASE_DMG) *
(CRIT DMG) * (DMG BONUS) * MELT? * ENEMY_DMG_REDUCE * ENEMY_RESISTANCE
*/
double baseDamage(Character& character, std::string talent) {
  std::string talentStatScaling = character.getTalentScalingStat(talent);
  double talentScalingDMG = character.getTalentScalingDMG(talent);

  return character.getStat(talentStatScaling) * talentScalingDMG;
}

double bonusMultipliers(Character& character) {
  double dmg_bonus = character.getDMGBonus(character.getElement());
  double crit_dmg = character.getStat("crit_damage");

  return 1 + dmg_bonus + crit_dmg;
}

double damageOutput(Character& character) {
  double baseDMG = baseDamage(character, BURST);
  double multipliers = bonusMultipliers(character);

  return baseDMG * multipliers;
}

// TODO: add melt bonus
double meltBonus(Character& character) {
  double EM = character.getStat("elemental_mastery");
  return 2.78 * (EM / 1400);
}

}  // namespace Calculator