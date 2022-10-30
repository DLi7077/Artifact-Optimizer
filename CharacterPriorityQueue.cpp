#include <iostream>
#include <queue>
#include <vector>
using namespace std;

class Compare {
 public:
  bool operator()(int curr, int incoming) {
    return curr * curr < incoming * incoming;
  }
};

int main() {
  priority_queue<int, vector<int>, Compare> x;
  x.push(10);
  x.push(-60);

  cout << x.top();
}