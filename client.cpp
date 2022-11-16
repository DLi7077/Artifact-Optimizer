#include "./Utils/optimize.cpp"
int main() {
  auto start = chrono::high_resolution_clock::now();

  Character Tartaglia(HYDRO);
  Tartaglia.setStat(BASE_ATK, 301 + 542);
  Tartaglia.setStat(CRIT_DAMAGE, 0.5 + 0.882);  // from weapon

  double weaponDMGBonus = 0.4;
  double ascensionDMGBonus = 0.288;
  double dmgBonusBuff = 0.838;
  double bonusAtkPercent = 1.08 + 0.14;

  Tartaglia.setStat(FLAT_ATK, 1491);
  Tartaglia.setStat(ATK_PERCENT, bonusAtkPercent);
  Tartaglia.setStat(ELEMENTAL_MASTERY, 567 + 180);
  Tartaglia.setStat(MELT_BONUS, .15);

  Tartaglia.setTalentDetails(BURST, "total_attack", 9.86);

  Tartaglia.setDamageBonus(HYDRO, ascensionDMGBonus + dmgBonusBuff);
  Tartaglia.setDamageBonus(ALL, weaponDMGBonus + 0.6);

  Enemy enemy(PYRO);
  enemy.setLevel(90);
  enemy.setResistance(HYDRO, 0.3 - 0.4 - 1.7);

  std::cout << Tartaglia;

  std::cout << enemy;

  Character best = Optimize::optimize(Tartaglia, enemy);

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  std::cout
      << "====== " << duration.count() << " ms\n"
      << "Program terminated successfully\n"
      << "=======================\n";

  return 0;
}