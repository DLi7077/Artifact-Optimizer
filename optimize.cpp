#include "./artifact.h"
#include "./constants.h"
#include "./generate.h"
#include "./stat.h"

using namespace std;

int main() {
  int substats = 4;
  int roll_count = 5;

  std::unordered_map<std::string, double>& maxRolls = Constants::getMaxRollMapping();

  vector<string> substat_labels = {
      ATK,
      ATK_PERCENT,
      HP,
      HP_PERCENT,
      DEF,
      DEF_PERCENT,
      ELEMENTAL_MASTERY,
      ENERGY_RECHARGE,
      CRIT_RATE,
      CRIT_DAMAGE};

  vector<vector<string>> possibleStartingStats = Generate::generateStartingStats(substat_labels, 4);

  std::array<std::string, SUBSTAT_COUNT> list = {
      ATK_PERCENT,
      CRIT_DAMAGE,
      CRIT_RATE,
      ELEMENTAL_MASTERY};

  Artifact x(list);

  vector<Artifact> result = Generate::generateArtifactOutcomes(x);

  cout << "\n===============================\n"
       << "Program terminated successfully"
       << "\n===============================";
  return 0;
}