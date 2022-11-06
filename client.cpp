#include "./optimize.cpp"

int main() {
  auto start = chrono::high_resolution_clock::now();

  Character Tartaglia(HYDRO);
  Enemy enemy(PYRO);

  std::cout << enemy;

  Optimize::optimize(Tartaglia, enemy);
 
  auto stop = chrono::high_resolution_clock::now();
  auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
  std::cout
      << "====== " << duration.count() << " ms\n"
      << "Program terminated successfully\n"
      << "=======================\n";
}