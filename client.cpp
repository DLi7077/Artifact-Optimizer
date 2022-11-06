#include "./optimize.cpp"

int main() {
  auto start = chrono::high_resolution_clock::now();

  Character Tartaglia(HYDRO);
  double weaponDMGBonus = 0.4;
  double ascensionDMGBonus = 0.28;
  double dmgBonusBuff = 0.838 + 0.6;
  double bonusAtkPercent = 1.08;

  Tartaglia.setStat(BASE_ATK, 301 + 542);
  Tartaglia.setStat(FLAT_ATK, 1491);
  Tartaglia.setStat(CRIT_DAMAGE, 0.5 + 0.882);
  Tartaglia.setStat(ATK_PERCENT, bonusAtkPercent);
  Tartaglia.setStat(ELEMENTAL_MASTERY, 567 + 180);
  Tartaglia.setTalentDetails(BURST, "total_attack", 9.86);

  std::cout << Tartaglia;

  Tartaglia.setDamageBonus(HYDRO, weaponDMGBonus + ascensionDMGBonus + dmgBonusBuff);

  Enemy enemy(PYRO);
  enemy.setResistance(HYDRO, 0.3 - 0.4 - 1.7);

  std::cout << enemy;

  Optimize::optimize(Tartaglia, enemy);

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  std::cout
      << "====== " << duration.count() << " ms\n"
      << "Program terminated successfully\n"
      << "=======================\n";

  return 0;
}