#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAX 500

long long memo[500][500];

string palabra;
int n;

long long borrar (int inicio, int fin) {
    long long resultado = MAX;

    if (inicio > fin) {
        return 0;
    }

    if (inicio == fin) {
        return 1;
    }

    if (memo[inicio][fin] != -1) {
        return memo[inicio][fin];
    }

    for (int k = inicio; k < fin; k++) {
        long long temporal = borrar(inicio, k) + borrar(k+1, fin);
        resultado = min(resultado, temporal);
    }

    for (int k = inicio+1; k <= fin; k++) {
        if (palabra[inicio] == palabra[k]) {
            long long temporal2 = borrar(inicio+1, k-1) + borrar(k, fin);
            resultado = min(resultado, temporal2);
        }
    }

    memo[inicio][fin] = resultado;
    return resultado;
}

int main () {
    cin >> n >> palabra;
    memset(memo, -1, sizeof(memo));

    long long res = borrar(0, n-1);
    cout << res << endl;

    return 0;
}