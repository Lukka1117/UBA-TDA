/*
hay un numero x que se quiere convertir en y, solo usando dos opciones

multiplicar el numero actual por 2 (2x)
añadir el 1 a la derecha ddel numero actual (10x+1)

pueden repetirse multiples veces
se quiere encontrar cualquier manera de transformar x en y o encontrar que es imposible

si no se puede se espera el mensaje NO
si se puede se espera que imprima una linea con YES, otra con la long de la secuencia de 
transformacion, y la tercera la secuencia de transformaciones

esto es backtracking, hay que ir probando todas las opciones para conseguir
candidatos a respuesta hasta qedarnos sin opciones
la idea es primer ver si x e y son iguales (si son, devolver el resultado),
y si x es menor q y, aplicarle una de las operaciones a x hasta que llegue a y, si en el proceso
se pasa de "y" vuelve un paso para atras y prueba con la otra operacion hasta llegar a "y" o
hasta necesitar cambiar de operacion nuevamente. 
si llega un punto que con las dos opciones falla, devuelve que no se puede convertir 
*/

#include <iostream>
#include <string>
#include <vector>
#include <tuple>
using namespace std;

vector<int> transformaciones;


//me da una tupla dnode la primera componente es YES si se puede llegar a y desde x, o NO en caso contrario
//y la segunda componente es la secuencia de transformacioones que se hacen para llegar y desde x
tuple<string, vector<int>> convertibilidad(int x, int y) {

    transformaciones.push_back(x);
    
    if (x == y) {
        return make_tuple("YES", transformaciones);
    }

    if (x > y) {
        transformaciones.pop_back(); 
        return make_tuple("NO", vector<int>());
    }
    
    //prueba multiplicando
    tuple<string, vector<int>> multiplicando = convertibilidad(2*x, y);
    if (get<0>(multiplicando) == "YES") {
        return multiplicando;
    }
    
    //prueba agregando el 1 
    tuple<string, vector<int>> appendeando1 = convertibilidad(10*x + 1, y);
    if (get<0>(appendeando1) == "YES") {
        return appendeando1;
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
    vector<int> transformacionesRes = get<1>(resultado);

    if (esPosible == "YES") {
        cout << esPosible << endl;
        cout << transformacionesRes.size() << endl;
        for (int i = 0; i < transformacionesRes.size(); i++) {
            cout << transformacionesRes[i] << " ";
        }
        cout << endl;
    } else {
        cout << esPosible << endl;
    }

    return 0;
}