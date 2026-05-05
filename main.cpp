#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
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

// Funciones Auxiliares para Streasen
Matriz sumar(const Matriz& a, const Matriz& b) {
  if(a.size() != b.size() || a.size() != a[0].size()) return Matriz();
  int n = a.size();
  Matriz c(n, vector<int>(n,0));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      c[i][j] = a[i][j] + b[i][j];
    }
  }
  return c;
}

Matriz restar(const Matriz& a, const Matriz& b) {
  if(a.size() != b.size() || a.size() != a[0].size()) return Matriz();
  int n = a.size();
  Matriz c(n, vector<int>(n,0));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      c[i][j] = a[i][j] - b[i][j];
    }
  }
  return c;
}

Matriz strassen(const Matriz& a, const Matriz& b) {
  if(a.size() != b.size() || a.size() != a[0].size()) return Matriz();
  int n = a.size();
  
}

void print(const Matriz& a) {
  int n = a.size();
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cout << setw(4) << a[i][j] << " ";
    }
    cout << endl;
  }
}

static long long elapsedNanoseconds(struct timespec start, struct timespec end) {
  long long seconds = (long long)(end.tv_sec - start.tv_sec);
  long long nanoseconds = (long long)(end.tv_nsec - start.tv_nsec);
  return seconds * 1000000000LL + nanoseconds;
}

int main(){
  srand(time(0));
  
  struct timespec start, end;
  
  for(int size = 10; size <= 500; size += 10) {
    Matriz A = generateMatriz(size);
    Matriz B = generateMatriz(size);

    /*cout << "Matriz A:" << endl;
    print(A);
    cout << "Matriz B:" << endl;
    print(B);
    */

    clock_gettime(CLOCK_MONOTONIC, &start);
    Matriz C = multiplyStandar(A, B);
    clock_gettime(CLOCK_MONOTONIC, &end);
  
    /*cout << "Matriz C:" << endl;  
    print(C);
    */

    double tiempo = (double)elapsedNanoseconds(start, end) / 1000.0;
    
    //Salida para gnuplot
    cout << size << " " << tiempo << endl;
    /*cout << "Tiempo de ejecucion: " << resultado << " us" << endl;*/
  }
  return 0;
}
