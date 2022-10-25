#include "./Character.h"
#include "./Enemy.h"
#include "utils.h"

namespace Calculator {
/**
 * @brief Calculates the melt and vaporize multiplier
 * @param EM the character's elemental mastery
 * @return double the bonus multiplier
 */
double meltVapeBonus(double EM) {
  return 2.78 * (EM / 1400);
}

}  // namespace Calculator
