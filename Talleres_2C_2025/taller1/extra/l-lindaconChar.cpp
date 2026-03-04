#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int cantidad_char_distintos(const char* cadena, char l) {
    int res = 0;

    for (int i = 0; i < strlen(cadena); i++) {
        if (cadena[i] != l) {
            res++;
        }
    }
    return res;
}

int movimientos_para_llinda(const char* cadena, int longitud, char l) {
    if (longitud == 1 && cadena[0] == l) {
        return 0;
   }
    if (longitud == 1 && cadena[0] != l) {
        return 1;
    }

    int medio = longitud / 2;
    char cadenaI[65537];  
    char cadenaD[65537];
    strncpy(cadenaI, cadena, medio);
    cadenaI[medio] = '\0';
    strncpy(cadenaD, cadena + medio, medio);
    cadenaD[medio] = '\0';
    
    int movimientos_caso_1 = cantidad_char_distintos(cadenaI, l) + movimientos_para_llinda(cadenaD, medio, l + 1);
    int movimientos_caso_2 = cantidad_char_distintos(cadenaD, l) + movimientos_para_llinda(cadenaI, medio, l + 1);

    return min(movimientos_caso_1, movimientos_caso_2);
}

int movimientos_para_obtener_aLinda(const char* cadena, int longitud) {
    return movimientos_para_llinda(cadena, longitud, 'a');
}

int main() {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) {
        int longitud;
        char cadena[131073];

        cin >> longitud;
        cin >> cadena;

        int movimientos_necesarios = movimientos_para_obtener_aLinda(cadena, longitud);
        cout << movimientos_necesarios << endl;
    }

    return 0;
}