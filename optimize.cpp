#include "./Artifact/artifact.h"
#include "./Constants/constants.h"
#include "./Game/DamageCalculator.cpp"
#include "./Game/character.h"
#include "./generate.h"

using namespace std;

template <class Item>
std::vector<Item> omit(const std::vector<Item>& original, const Item& toRemove) {
  std::vector<Item> result;
  result.reserve(original.size());

  for (Item item : original) {
    if (item == toRemove) continue;
    result.push_back(item);
  }

  return result;
}

vector<Artifact> generateArtifactsForPiece(string pieceName) {
  vector<Artifact> result;
  vector<string>& possibleMainStats = Constants::artifact_main_stats_[pieceName];

  // consider every possible main stat
  for (string& mainStat : possibleMainStats) {
    // generate possible starting stats
    vector<string> possibleSubstats = omit(Constants::possible_substats_, mainStat);
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

const ArtifactSet bestArtifactCombination(Character& character,
                                          Enemy& enemy,
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

      // for (Artifact& sands : SandsArtifacts) {
      //   character.addArtifact(sands);

      //   for (Artifact& goblet : GobletArtifacts) {
      //     character.addArtifact(goblet);

      //     for (Artifact& circlet : CircletArtifacts) {
      //       character.addArtifact(circlet);
      double damageOutput = Calculator::damageOutput(character, enemy);

      if (highestDamage < damageOutput) {
        highestDamage = damageOutput;
        best.flower = flower;
        best.feather = feather;
        // best.sands = sands;
        // best.goblet = goblet;
        // best.circlet = circlet;
      }
      //       character.removeArtifact(circlet);
      //     }

      //     character.removeArtifact(goblet);
      //   }

      //   character.removeArtifact(sands);
      // }

      character.removeArtifact(feather);
    }

    character.removeArtifact(flower);
  }

  return best;
}

int main() {
  int substats = 4;
  int roll_count = 5;

  vector<Artifact> FlowerArtifacts = generateArtifactsForPiece(FLOWER);
  vector<Artifact> FeatherArtifacts = generateArtifactsForPiece(FEATHER);
  vector<Artifact> SandsArtifacts = generateArtifactsForPiece(SANDS);
  vector<Artifact> GobletArtifacts = generateArtifactsForPiece(GOBLET);
  vector<Artifact> CircletArtifacts = generateArtifactsForPiece(CIRCLET);

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

  cout
      << "\n===============================\n"
      << "Program terminated successfully"
      << "\n===============================";
  return 0;
}
