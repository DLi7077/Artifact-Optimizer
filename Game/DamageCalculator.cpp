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
  double dmg_bonus = character.getDMGBonus(character.getDamageElement());
  double crit_dmg = character.getStat("crit_damage");

  return 1 + dmg_bonus + crit_dmg;
}

// TODO: add melt bonus
double meltBonus(Character& character) {
  double EM = character.getStat("elemental_mastery");
  return 2.78 * (EM / 1400);
}

double damageReductionByDefense(Character& character, Enemy& enemy) {
  int characterLevel = character.getLevel();
  int enemyLevel = enemy.getLevel();

  // TODO: add defense shred
  double enemyDefense = 5 * enemyLevel + 500;
  double DMGReduction = enemyDefense / double(enemyDefense + (5 * characterLevel) + 500);

  return DMGReduction;
}

double enemyElementResistance(Character& character, Enemy& enemy) {
  std::string& damageElement = character.getDamageElement();
  double resistance = enemy.getResistance(damageElement);

  if (resistance < 0) {
    return 1 - (resistance / 2);
  }

  if (resistance >= 0.75) {
    return 1 / (4 * resistance + 1);
  }

  return 1 - resistance;
}

double damageOutput(Character& character, Enemy& enemy) {
  double baseDMG = baseDamage(character, BURST);
  double multipliers = bonusMultipliers(character);
  double DMGReducedPercent = 1 - damageReductionByDefense(character, enemy);
  double resistanceMultiplier = enemyElementResistance(character, enemy);

  return baseDMG * multipliers * DMGReducedPercent * resistanceMultiplier;
}

}  // namespace Calculator