#include <chrono>

#include "./Artifact/artifact.h"
#include "./Constants/constants.h"
#include "./Game/DamageCalculator.cpp"
#include "./Game/character.h"
#include "./Utils/utils.cpp"
#include "./generate.h"

using namespace std;

vector<Artifact> generateArtifacts(
    vector<string>& mainStatPool,
    vector<string>& substatPool = Constants::possible_substats_) {
  vector<Artifact> result;

  // consider every possible main stat
  for (string& mainStat : mainStatPool) {
    // generate possible starting stats
    vector<string> possibleSubstats = Utils::omit(substatPool, mainStat);
    vector<Artifact> startingStats = Generate::generateStartingArtifacts(mainStat, possibleSubstats);

    // generate rolls for each base artifact
    for (Artifact& baseArtifact : startingStats) {
      vector<Artifact> artifactRollResults = Generate::generateArtifactOutcomes(baseArtifact);

      // add every possible roll outcome for every artifact to result
      for (Artifact& rollResult : artifactRollResults) {
        result.push_back(move(rollResult));
      }
    }
  }

  return result;
}

struct ArtifactSet {
  Artifact flower;
  Artifact feather;
  Artifact sands;
  Artifact goblet;
  Artifact circlet;
};

const ArtifactSet bestArtifactCombination(
    Character& character, Enemy& enemy,
    vector<Artifact>& FlowerArtifacts,
    vector<Artifact>& FeatherArtifacts,
    vector<Artifact>& SandsArtifacts,
    vector<Artifact>& GobletArtifacts,
    vector<Artifact>& CircletArtifacts) {
  ArtifactSet best;
  double highestDamage = 0;
  for (Artifact& flower : FlowerArtifacts) {
    character.addArtifact(flower);

    for (Artifact& feather : FeatherArtifacts) {
      character.addArtifact(feather);

      for (Artifact& sands : SandsArtifacts) {
        character.addArtifact(sands);

        // for (Artifact& goblet : GobletArtifacts) {
        //   character.addArtifact(goblet);

        //   for (Artifact& circlet : CircletArtifacts) {
        //     character.addArtifact(circlet);
        double damageOutput = Calculator::damageOutput(character, enemy);

        if (highestDamage < damageOutput) {
          highestDamage = damageOutput;
          best.flower = flower;
          best.feather = feather;
          best.sands = sands;
          // best.goblet = goblet;
          // best.circlet = circlet;
        }
        //     character.removeArtifact(circlet);
        //   }
        //   character.removeArtifact(goblet);
        // }
        character.removeArtifact(sands);
      }
      character.removeArtifact(feather);
    }
    character.removeArtifact(flower);
  }

  return best;
}

int main() {
  auto start = chrono::high_resolution_clock::now();
  int substats = 4;
  int roll_count = 5;
  vector<string> subStatPreference = {
      FLAT_ATK,
      ATK_PERCENT,
      ENERGY_RECHARGE,
      ELEMENTAL_MASTERY,
      CRIT_DAMAGE,
  };

  vector<string> mainStatPreference = {
      FLAT_HP,   // Flower
      FLAT_ATK,  // Feather
      ATK_PERCENT,
      ELEMENTAL_MASTERY,
      CRYO_DAMAGE_BONUS,
      CRIT_DAMAGE,
  };

  vector<string> mainStatGobletPref = {
      CRYO_DAMAGE_BONUS,
  };
  vector<string> mainStatCircletPref = {
      CRIT_DAMAGE,
  };

  vector<string>
      FlowerMainPref = Utils::intersection(Constants::artifact_main_stats_[FLOWER], mainStatPreference);
  vector<string> FeatherMainPref = Utils::intersection(Constants::artifact_main_stats_[FEATHER], mainStatPreference);
  vector<string> SandsMainPref = Utils::intersection(Constants::artifact_main_stats_[SANDS], mainStatPreference);
  vector<string> GobletMainPref = Utils::intersection(Constants::artifact_main_stats_[GOBLET], mainStatGobletPref);
  vector<string> CircletMainPref = Utils::intersection(Constants::artifact_main_stats_[CIRCLET], mainStatCircletPref);

  for (string x : mainStatGobletPref) cout << x << "\n";

  vector<Artifact> FlowerArtifacts = generateArtifacts(FlowerMainPref, subStatPreference);
  vector<Artifact> FeatherArtifacts = generateArtifacts(FeatherMainPref, subStatPreference);
  vector<Artifact> SandsArtifacts = generateArtifacts(SandsMainPref, subStatPreference);
  vector<Artifact> GobletArtifacts = generateArtifacts(GobletMainPref, subStatPreference);
  vector<Artifact> CircletArtifacts = generateArtifacts(CircletMainPref, subStatPreference);

  cout << "Flower Artifacts:\t" << FlowerArtifacts.size() << "\n";
  cout << "Feather Artifacts:\t" << FeatherArtifacts.size() << "\n";
  cout << "Sands Artifacts:\t" << SandsArtifacts.size() << "\n";
  cout << "Goblet Artifacts:\t" << GobletArtifacts.size() << "\n";
  cout << "Circlet Artifacts:\t" << CircletArtifacts.size() << "\n\n";

  Character character(CRYO);
  Enemy enemy;

  ArtifactSet best = bestArtifactCombination(character, enemy,
                                             FlowerArtifacts, FeatherArtifacts, SandsArtifacts, GobletArtifacts, CircletArtifacts);
  cout << best.flower << '\n';
  cout << best.feather << '\n';
  cout << best.sands << '\n';

  auto stop = chrono::high_resolution_clock::now();

  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

  cout
      << "\n===============================\n"
      << "======" << duration.count() << "ms======\n"
      << "Program terminated successfully"
      << "\n===============================";
  return 0;
}
