#include "../Constants/constants.h"
#include "../Constants/pch.h"
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

  return (1 + dmg_bonus) * (1 + crit_dmg);
}

// TODO: add crimson witch buffs
double meltBonus(Character& character, Enemy& enemy) {
  double EM = character.getStat("elemental_mastery");
  std::string dmgElement = character.getDamageElement();
  std::string enemyElement = enemy.getAffectedElement();
  double reactionBonus = 1 + (2.78 * (EM / (EM + 1400)));

  double multiplier = 1;
  if (dmgElement == PYRO && enemyElement == CRYO)
    multiplier = 2 * reactionBonus;
  else if (dmgElement == CRYO && enemyElement == PYRO)
    multiplier = 1.5 * reactionBonus;
  else if (dmgElement == HYDRO && enemyElement == PYRO)
    multiplier = 2 * reactionBonus;
  else if (dmgElement == PYRO && enemyElement == HYDRO)
    multiplier = 1.5 * reactionBonus;

  return multiplier;
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
  double meltVapMultiplier = meltBonus(character, enemy);

  return baseDMG *
         multipliers *
         DMGReducedPercent *
         resistanceMultiplier *
         meltVapMultiplier;
}

}  // namespace Calculator