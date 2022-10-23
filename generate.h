#pragma once
#include "./Artifact/artifact.h"
#include "./Constants/utils.h"

using namespace std;

class Generate {
 public:
  /**
   * @brief Generates all possible distributions of rolls into substats
   * Removes duplicates
   * @param substats number of substats
   * @param rolls number of rolls
   * @return vector<vector<int>> all possible distributions
   */
  static vector<vector<int>> generateRolls(int substats, int rolls) {
    vector<vector<int>> result;
    unordered_set<string> duplicates;

    vector<int> base(substats, 0);
    dfs(result, duplicates, base, rolls);

    return result;
  }

  // Generates Combinations of starting substats - Leetcode Combinations
  template <typename Object>
  static vector<vector<Object>> generateStartingStats(vector<Object> &substats, int startingStats, int start = 0) {
    if (start == substats.size() || startingStats <= 0) {
      return {{}};
    }

    vector<vector<Object>> result;
    for (int i = start; i < substats.size() - (startingStats - 1); i++) {
      vector<vector<Object>> subResult = generateStartingStats(substats, startingStats - 1, i + 1);

      for (vector<Object> &sub : subResult) {
        sub.insert(sub.begin(), substats[i]);

        result.push_back(sub);
      }
    }

    return result;
  }

  static vector<Artifact> generateStartingArtifacts(vector<string> &substats) {
    vector<Artifact> result;
    for (int i = 0; i < substats.size(); i++) {
      string mainStat = substats[i];
      vector<string> substatPools = substats;
      substatPools.erase(substatPools.begin() + i);

      vector<vector<string>> startingStats = generateStartingStats(substatPools, SUBSTAT_COUNT);
      for (vector<string> &startingStat : startingStats) {
        array<string, SUBSTAT_COUNT> startingSubstats;

        for (int i = 0; i < SUBSTAT_COUNT; i++) {
          startingSubstats[i] = move(startingStat[i]);
          cout << startingSubstats[i] << "\n";
        }

        // result.push_back(Artifact({}, mainStat));
      }
    }

    return result;
  }

  /**
   * @brief Given an artifact, generates all possible outcomes using max rolls
   *
   * @param artifact An artifact with no extra rolls at lv. 0
   * @return vector<Artifact> A list of all possible outcomes
   */
  static vector<Artifact> generateArtifactOutcomes(const Artifact &artifact) {
    vector<vector<int>> rollDistributions = generateRolls(SUBSTAT_COUNT, ROLL_COUNT);
    vector<Artifact> outcomes(rollDistributions.size(), artifact);

    // add rolls to each copy artifact
    for (size_t roll = 0; roll < rollDistributions.size(); roll++) {
      Artifact &curr = outcomes[roll];

      for (size_t value = 0; value < SUBSTAT_COUNT; value++) {
        curr[value].addRolls(rollDistributions[roll][value]);
      }
      cout << curr;
    }

    return outcomes;
  }

 private:
  static string serialize(vector<int> &list) {
    string result = "";
    for (int i : list) result += to_string(i) + " ";

    return result;
  }

  static void dfs(vector<vector<int>> &result, unordered_set<string> &duplicates, vector<int> &substats, int rolls) {
    if (rolls == 0) {
      result.push_back(substats);
      return;
    }

    for (size_t i = 0; i < substats.size(); i++) {
      substats[i]++;

      string serialized = serialize(substats);
      if (duplicates.count(serialized)) {
        substats[i]--;
        continue;
      }
      duplicates.insert(serialized);

      dfs(result, duplicates, substats, rolls - 1);
      substats[i]--;
    }
  }
};