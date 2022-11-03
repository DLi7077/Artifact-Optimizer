#include <cmath>

#include "./Artifact/artifact.h"
#include "./Constants/constants.h"
#include "./Game/DamageCalculator.cpp"
#include "./Game/character.h"
#include "./Utils/initializer.cpp"

int main() {
  auto start = chrono::high_resolution_clock::now();

  std::cout << "Flower Artifacts:\t" << Initial::FlowerArtifacts.size() << "\n";
  std::cout << "Feather Artifacts:\t" << Initial::FeatherArtifacts.size() << "\n";
  std::cout << "Sands Artifacts:\t" << Initial::SandsArtifacts.size() << "\n";
  std::cout << "Goblet Artifacts:\t" << Initial::GobletArtifacts.size() << "\n";
  std::cout << "Circlet Artifacts:\t" << Initial::CircletArtifacts.size() << "\n\n";

  std::vector<std::vector<Artifact>> artifactSets = {
      std::move(Initial::FlowerArtifacts),
      std::move(Initial::FeatherArtifacts),
      std::move(Initial::SandsArtifacts),
      std::move(Initial::GobletArtifacts),
      std::move(Initial::CircletArtifacts),
  };

  struct DamageComparator {
   public:
    Enemy enemy;
    bool operator()(Character a, Character b) {
      double damageA = Calculator::damageOutput(a, enemy);
      double damageB = Calculator::damageOutput(b, enemy);
      return damageA > damageB;
    }
  };

  const size_t limit = 20;
  Character base(CRYO);
  std::vector<Character> population = {base};

  std::priority_queue<Character, std::vector<Character>, DamageComparator> minHeap;
  for (std::vector<Artifact>& artifactPool : artifactSets) {
    for (Character character : population) {
      for (Artifact& piece : artifactPool) {
        Character curr = character;
        curr.addArtifact(piece);
        minHeap.push(curr);

        if (minHeap.size() > limit) {
          minHeap.pop();
        }
      }
    }
    population.clear();
    while (minHeap.size()) {
      population.push_back(minHeap.top());
      minHeap.pop();
    }
  }

  Enemy enemy;

  Character x = population[19];
  std::vector<Artifact> as = x.getArtifacts();
  std::cout << as.size();

  for (Artifact& y : as) std::cout << y;

  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);

  std::cout
      << "\n===============================\n"
      << "======" << duration.count() << "ms======\n"
      << "Program terminated successfully"
      << "\n===============================";
  return 0;
}
