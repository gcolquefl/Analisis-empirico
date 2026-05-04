#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

typedef vector<vector<int>> Matriz;

Matriz generateMatriz(int n) {
  Matriz newMatriz(n, vector<int>(n, 0));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      newMatriz[i][j] = rand() % 10;
    }
  }
  return newMatriz;
}

Matriz multiplyStandar(const Matriz& a, const Matriz& b) {
  if(a.size() == 0 || b.size() == 0 || a.size() != b.size() ||
      a[0].size() != b[0].size() || a.size() != a[0].size()) {
    cout << "Dimensiones invalidas" << endl;
    return Matriz();
  }

  int n = a.size();
  Matriz c(n, vector<int>(n, 0));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      for(int k = 0; k < n; k++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return c;
}

void print(const Matriz& a) {
  int n = a.size();
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cout << "Matriz[" << i << "][" << j <<"] = " << a[i][j] << endl;
    }
  }
}

int main(){
  srand(time(0));
  Matriz A = generateMatriz(2);
  Matriz B = generateMatriz(2);
  cout << "Matriz A:" << endl;
  print(A);
  cout << "Matriz B:" << endl;
  print(B);

  cout << "Matriz C:" << endl;
  Matriz C = multiplyStandar(A, B);
  print(C);

  return 0;
}
