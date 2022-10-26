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

  Character test(CRYO);
  test.addArtifact(FlowerArtifacts[7055]);
  test.addArtifact(FeatherArtifacts[7055]);
  test.addArtifact(SandsArtifacts[10000]);
  test.addArtifact(GobletArtifacts[40000]);
  test.addArtifact(CircletArtifacts[10000]);

  cout << test;
  double dmg = Calculator::damageOutput(test) ;
  cout << dmg;

  cout
      << "\n===============================\n"
      << "Program terminated successfully"
      << "\n===============================";
  return 0;
}
