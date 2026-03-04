/*
hay un numero x que se quiere convertir en y, solo usando dos opciones

multiplicar el numero actual por 2 (2x)
añadir el 1 a la derecha ddel numero actual (10x+1)

pueden repetirse multiples veces
se quiere encontrar cualquier manera de transformar x en y o encontrar que es imposible

si no se puede se espera el mensaje NO
si se puede se espera que imprima una linea con YES, otra con la long de la secuencia de 
transformacion, y la tercera la secuencia de transformaciones

hay que ir probando todas las opciones para conseguir candidatos a respuesta hasta qedarnos sin opciones
la idea es primer ver si x e y son iguales (si son, devolver el resultado), 
quise hacer backtracking desde x a y no me daban los tiempos asi que lo cambie a que mire de y a x,
entonces puede ser mas facil elegir que camino tomar, ya que si y es par lo puedo dividir por 2 para conseguir el 
nnumero anterior, o si y termina en 1 hago (y-1) / 10 para consegur el numero anterior. Me parece que teninendo un 
criterio sobre quue camino tomar deberia ahorrase varios caminos fallidos.
asi que ahora mientras x < y, la idea es ver cual operacion se le puede hacer a y para llegar alnum anterior
y eventualmente llegar a x. Si no se llega a x, no se puede
*/

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <algorithm>
using namespace std;

vector<int> transformaciones;

//me da una tupla dnode la primera componente es YES si se puede llegar a y desde x, o NO en caso contrario
//y la segunda componente es la secuencia de transformacioones que se hacen para llegar a x desde y
tuple<string, vector<int>> convertibilidad(int x, int y) {

    transformaciones.push_back(y);
    
    if (x == y) {
        return make_tuple("YES", transformaciones);
    }

    if (x > y) {
        transformaciones.pop_back(); 
        return make_tuple("NO", vector<int>());
    }
    
    //si y es par se llama recursivamente con y/2
    if (y % 2 == 0) {
        tuple<string, vector<int>> dividiendoy = convertibilidad(x, y/2);
        if (get<0>(dividiendoy) == "YES") {
            return dividiendoy;
        }
    }
    
    //si y termina en 1 se llama recursivamente con (y-1)/10
    if (y % 10 == 1) {
        tuple<string, vector<int>> appendeando1 = convertibilidad(x, (y-1)/10);
        if (get<0>(appendeando1) == "YES") {
            return appendeando1;
        }
    }
    
    //si no funca ninguno vuelve para atras y devuelve que no se puede
    transformaciones.pop_back();
    return make_tuple("NO", vector<int>());
}

int main() {

    int x, y;
    cin >> x >> y;

    tuple<string, vector<int>> resultado = convertibilidad(x, y);
    string esPosible = get<0>(resultado);
    vector<int> transformaciones = get<1>(resultado);
    reverse(transformaciones.begin(), transformaciones.end());

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