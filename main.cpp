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

Matriz multiplyStandar(const Matriz& a, const Matriz& b, int n) {
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
    
int main(){
  srand(time(0));
  
}
