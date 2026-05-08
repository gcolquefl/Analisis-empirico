#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>
using namespace std;

typedef vector<vector<int>> Matriz;
const int THRESHOLD = 32;

// Genera matriz con números aleatorios
Matriz generateMatriz(int n) {
  Matriz newMatriz(n, vector<int>(n, 0));
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      newMatriz[i][j] = rand() % 10;
    }
  }
  return newMatriz;
}

// Multiplicación Estándar
Matriz multiplyStandar(const Matriz& a, const Matriz& b) {
  if(a.size() == 0 || b.size() == 0 || a.size() != b.size() ||
      a[0].size() != b[0].size() || a.size() != a[0].size()) {
    return Matriz();
  }
  int n = a.size();
  Matriz c(n, vector<int>(n, 0));
  // Orden i-k-j mejor localidad de caché (b recorre filas, no columnas)
  for(int i = 0; i < n; i++) {
    for(int k = 0; k < n; k++) {
      for(int j = 0; j < n; j++) {
        c[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return c;
}

// Funciones Auxiliares para Streasen(Suma y Resta)
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

// Función Strassen
Matriz strassen(const Matriz& a, const Matriz& b) {
  if(a.size() != b.size() || a.size() != a[0].size()) return Matriz();
  int n = a.size();
  if(n <= THRESHOLD) return multiplyStandar(a, b);

  int k = n / 2;

  Matriz A11(k, vector<int>(k)), A12(k, vector<int>(k)), 
         A21(k, vector<int>(k)), A22(k, vector<int>(k));
  Matriz B11(k, vector<int>(k)), B12(k, vector<int>(k)),
         B21(k, vector<int>(k)), B22(k, vector<int>(k));

  for(int i = 0; i < k; i++) {
    for(int j = 0; j < k; j++) {
      A11[i][j] = a[i][j];
      A12[i][j] = a[i][j + k];
      A21[i][j] = a[i + k][j];
      A22[i][j] = a[i + k][j + k];

      B11[i][j] = b[i][j];
      B12[i][j] = b[i][j + k];
      B21[i][j] = b[i + k][j];
      B22[i][j] = b[i + k][j + k];
    }
  }
  
  Matriz M1 = strassen(sumar(A11, A22), sumar(B11, B22));
  Matriz M2 = strassen(sumar(A21, A22), B11);
  Matriz M3 = strassen(A11, restar(B12, B22));
  Matriz M4 = strassen(A22, restar(B21, B11));
  Matriz M5 = strassen(sumar(A11, A12), B22);
  Matriz M6 = strassen(restar(A21, A11), sumar(B11, B12));
  Matriz M7 = strassen(restar(A12, A22), sumar(B21, B22));
  
  Matriz c(n, vector<int>(n));
  for(int i = 0; i < k; i++) {
    for(int j = 0; j < k; j++) {
      c[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j]; //C11
      c[i][j + k] = M3[i][j] + M5[i][j];  //C12
      c[i + k][j] = M2[i][j] + M4[i][j];  //C21
      c[i + k][j + k] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j]; //C22
    }
  }
  return c;
}

// Mostrar Matriz
void print(const Matriz& a) {
  int n = a.size();
  for(int i = 0; i < n; i++) {
    for(int j = 0; j < n; j++) {
      cout << setw(4) << a[i][j] << " ";
    }
    cout << endl;
  }
}

// Calcula la diferencia de tiempo total
static long long elapsedNanoseconds(struct timespec start, struct timespec end) {
  long long seconds = (long long)(end.tv_sec - start.tv_sec);
  long long nanoseconds = (long long)(end.tv_nsec - start.tv_nsec);
  return seconds * 1000000000LL + nanoseconds;
}

// Tiempo de ejecución de Algoritmo Estándar
static double measureStandar(const Matriz& A, const Matriz& B) {
  struct timespec start;
  struct timespec end;

  clock_gettime(CLOCK_MONOTONIC, &start);
  multiplyStandar(A, B);
  clock_gettime(CLOCK_MONOTONIC, &end);

  return (double)elapsedNanoseconds(start, end) / 1000.0;
}

// Tiempo de ejecución de Algoritmo de Strassen
static double measureStrassen(const Matriz& A, const Matriz& B) {
  struct timespec start;
  struct timespec end;

  clock_gettime(CLOCK_MONOTONIC, &start);
  strassen(A, B);
  clock_gettime(CLOCK_MONOTONIC, &end);

  return (double)elapsedNanoseconds(start, end) / 1000.0;
}

int main(){
  srand(time(0));
  const int REPETICIONES = 10;
  cout << "# n tiempo_standar tiempo_strassen" << endl;
  
  vector<int> sizes = {2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

  for(int size : sizes) {
    Matriz A = generateMatriz(size);
    Matriz B = generateMatriz(size);
    
    double totalStandar = 0;
    double totalStrassen = 0;

    for(int i = 0; i < REPETICIONES; i++) {
      totalStandar += measureStandar(A, B);
      totalStrassen += measureStrassen(A, B);
    }

    double tStandar = totalStandar / REPETICIONES;
    double tStrassen = totalStrassen / REPETICIONES;
    
    cout << size << " " << tStandar << " " << tStrassen << endl;
  }

  return 0;
}
