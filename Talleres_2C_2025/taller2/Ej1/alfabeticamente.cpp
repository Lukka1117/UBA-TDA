/*
tenemos n strings para ordenar alfabeticamente pero no se pueden cambiar de lugar, solo dar vuelta algunas
dos palabras iguales consecutivas se consideran ordenadas
para dar vuelta el string i se consumen c[i] unidades de energia
se quiere mnimizar la cantidad de energia que necestia gastar para que las apalbraas queden en orden

input:
La primera línea del input contiene un entero n(2≤n≤100.000), la cantidad de palabras.
La siguiente línea contiene los n enteros ci(0≤ci≤109).
Las últimas n líneas contienen cada uno de los strings a ordenar. 
La longitud total de estos strings es menor o igual a 100.000 caracteres.

output:
Si es imposible invertir algunas (posiblemente 0) de las strings para que queden ordenadas alfabéticamente, 
imprimir -1. 
En caso contrario, imprimir la mínima cantidad de energía que Juan necesita gastar para lograr su objetivo.

para este problema, pense esta funcion

alf(i, ult) = {0                                                si i = n}
              {res = min(res, alf(i+1, 0))                      si i > n and strings[i-1] <= strings[i]}
              {res = min(res, costos[i] + alf(i+1, 1)))         si i > n and strings[i-1] <= stringsAlreves[i]}
              {INF                                              cc}

y ´de llamada inicial seria alf(0, 0), por que llamo con el primer string, y al no tener ningun string anterior
siempre va a tener estado normal (sin darlo vuelta)

en superposicion de estados tenemos
estados: n strings y 2 posibles casos --> O(2n) = O(n) estados
llamados recursivos: el arbol de rec tiene altura n, y el numero de llamadas recursivas que genera c/llamada
de funcion es 2. siemmpre llama 2 subproblemas distintos en cada paso, entonces en el peor caso nos quedan Ω(2^n) 
llamados recursivos

o sea que no necesitamos condiciones sobre n porq siempre se cumple que n < (2^n)

y la complejidad me queda en O(n) porq llenar la matriz me cuesta O(2n) = O(n)
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define INF 1e18
#define anteriorNormal 0
#define anteriorAlReves 1

long long memo[100000][2];
vector<long long> costos;
vector<string> palabras;
vector<string> palabrasAlReves;
int n;


//funcion para setear las variables globales con los inputs
void inputs() {

    costos.assign(n, 0);
    palabras.assign(n, ""); 
    palabrasAlReves.assign(n, "");

    for (int i = 0; i < n; i++) {
        cin >> costos[i];
    }
    
    for (int i = 0; i < n; i++) {
        cin >> palabras[i];
        palabrasAlReves[i] = palabras[i];
        reverse(palabrasAlReves[i].begin(), palabrasAlReves[i].end());
    }
}

long long alfabeticamente (int i, int estadoDeAnterior) {

    long long res = INF;

    //no tengo mas strings para ver
    if (i == n) { 
        return 0;
    }

    if (memo[i][estadoDeAnterior] != -1) {
        return memo[i][estadoDeAnterior];
    }

    string anterior;

    if (i == 0) {
        anterior = "";
    } else {
        if (estadoDeAnterior == anteriorNormal) {
            anterior = palabras[i-1];
        } else {
            anterior = palabrasAlReves[i-1];
        }
    }

    //dejo el str como esta
    if (anterior <= palabras[i]) {
        long long actualMantiene = alfabeticamente(i + 1, anteriorNormal);
        res = min(res, actualMantiene);
    }

    //doy vuelta el str actual
    if (anterior <= palabrasAlReves[i]) {
        long long actualSeDaVuelta = alfabeticamente(i + 1, anteriorAlReves);
        res= min(res, costos[i] + actualSeDaVuelta);
    }

    memo[i][estadoDeAnterior] = res;
    return res;

}


int main() {
    cin >> n;

    inputs();
    memset(memo, -1, sizeof(memo));

    long long res = alfabeticamente(0, anteriorNormal);

    if (res >= INF) {
        cout << -1 << endl;
    } else {
        cout << res << endl;
    }
}