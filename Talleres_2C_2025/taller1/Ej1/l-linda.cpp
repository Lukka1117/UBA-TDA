/*
tengo un string s[1...n] que es l-lindo si:
o bien |s| = 1, y ese unico caracter es l
o bien |s| > 1, la primera mitad de s esta compuesta solo por l, y la segunda mitad es un (l + 1)lindo
o bien |s| > 1, la primera mitad de s es un (l + 1)lindo, y la segunda mitad esta compuesta solo por l
la longitud de las cadenas siempre va a ser alguna potencia de 2

lo voy a trbajar con el método de divide&conquer

la idea es, primero ver si el string tiene una sola letra, si esa es "a", no necesita ningun cambio,
pero si es otra necesita 1. Ese seria mi caso base
Despues analizar los dos casos restantes, dividiendo la cadena a la mitad para poder calcular
cuantos cambios necesito hacer en una mitad para que sea todo "a", y cuantos cambios necesita la
otra mitad para cumplir con las caracteristicas de palabra (l+1)-linda (calculado recursivamente).
Luego, al unir los movimientos de las dos mitades, me quedan dos posibles casos de movimientos 
necesarios (el caso donde la primera mitad es "a" o cuando la segunda miad es "a"), pero como me pide
la menor cantidad de cambios necesarios, pido el minimo entre esos dos.
*/

#include <iostream>
#include <string>
using namespace std;

//calcula cuantos char en una cadena son distintos al char pasado por parametro
int cantidad_char_distintos(string cadena, char l) {
    
    int res = 0;

    for (int i = 0; i < cadena.length(); i++) {
        if (cadena[i] != l) {
            res++;
        }
    }
    return res;
}

//calcula los movimientos necesarios para transformar una cadena en l-linda valida, usando D&C
int movimientos_para_obtener_llinda(string cadena, int longitud, char l) {

    //el caso base cuando el string es de 1 caracter, si es l no hace cambios, 
    //si no, necesita 1 movimiento para cambiar ese caracter a l
    if (longitud == 1 && cadena[0] == l) {
        return 0;
   }
    if (longitud == 1 && cadena[0] != l) {
        return 1;
    }

    int medio = longitud / 2;
    string cadenaI = cadena.substr(0, medio);
    string cadenaD = cadena.substr(medio);

    //caso donde la primera mitad es todo l
    int movimientos_caso_1 = cantidad_char_distintos(cadenaI, l) + movimientos_para_obtener_llinda(cadenaD, medio, l + 1);
    //caso donde la primera mitad es todo l
    int movimientos_caso_2 = cantidad_char_distintos(cadenaD, l) + movimientos_para_obtener_llinda(cadenaI, medio, l + 1);

    //devuelve la opcion de cambios que haya necesitado menos movimientos
    return min(movimientos_caso_1, movimientos_caso_2); 
}


int main() {

    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int longitud;
        string cadena;

        cin >> longitud;
        cin >> cadena;

        int movimientos_necesarios = movimientos_para_obtener_llinda(cadena, longitud, 'a');
        cout << movimientos_necesarios << endl;
    }

    return 0;
}