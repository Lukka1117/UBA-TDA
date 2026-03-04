/*
hay un numero x que se quiere convertir en y, solo usando dos opciones

multiplicar el numero actual por 2 (2x)
añadir el 1 a la derecha ddel numero actual (10x+1)

pueden repetirse multiples veces
se quiere encontrar cualquier manera de transformar x en y o encontrar que es imposible

si no se puede se espera el mensaje NO
si se puede se espera que imprima una linea con YES, otra con la long de la secuencia de 
transformacion, y la tercera la secuencia de transformaciones

esto es backtracking, hay que ir probando todas las opciones hasta conseguir
candidatos a respuesta hasta qedarnos sin opciones
*/

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

tuple<string, vector<int>> convertibilidad (int x, int y) {
    
    if (x == y) {
        vector<int> transformaciones = {x};
        return make_tuple("YES", transformaciones);
    }
    if (x > y) {
        return make_tuple("NO", vector<int>());
    }

    tuple<string, vector<int>> multiplicando = convertibilidad(2*x, y);
    if (get<0>(multiplicando) == "YES") {
        vector<int> transformaciones = get<1>(multiplicando);
        transformaciones.insert(transformaciones.begin(), x);
        return make_tuple("YES", transformaciones);
    }

    tuple<string, vector<int>> añadiendo1 = convertibilidad(10*x + 1, y);
    if (get<0>(añadiendo1) == "YES") {
        vector<int> transformaciones = get<1>(añadiendo1);
        transformaciones.insert(transformaciones.begin(), x);
        return make_tuple("YES", transformaciones);
    }

    return make_tuple("NO", vector<int>());

}

int main() {
    int x;
    int y;
    cin >> x;
    cin >> y;

    tuple<string, vector<int>> resultado = convertibilidad(x, y);
    string esPosible = get<0>(resultado);
    vector<int> transformaciones = get<1>(resultado);

    if (esPosible == "YES") {
        cout << esPosible << endl;
        cout << transformaciones.size() << endl;
        for (int i = 0; i < transformaciones.size(); i++) {
            cout << transformaciones[i] << " ";
        }
        cout << endl;
    } else {
        cout << esPosible << endl;
    }

    return 0;
}