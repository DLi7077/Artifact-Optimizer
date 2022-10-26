#include "../Constants/constants.h"
#include "../Constants/utils.h"
#include "./Character.h"
#include "./Enemy.h"

namespace Calculator {

}  // namespace Calculator

using namespace std;
int main() {
  Character test;
  test.setStat(BASE_ATK, 700);
  test.setStat(ATK_PERCENT, 100);
  test.setStat(FLAT_ATK, 1);
  StatModel x = test.finalStats();

  cout << test;
}
