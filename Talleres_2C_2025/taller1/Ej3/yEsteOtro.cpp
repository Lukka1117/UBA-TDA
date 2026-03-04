#include <iostream>
#include <string>
#include <vector>
using namespace std;

int longitud_desplegado(int n) {
    if (n == 1 || n == 0) {
        return 1;
    } else {
        return 2*longitud_desplegado(n/2) + 1;
    }
}

//expande n a una lista recursivamente con las operaciones q me pide
tuple<int, int> cantidad_unos_y_ceros(int n, int l, int r) {

    if (n == 1) {
        return make_tuple(1, 0);
    }
    if (n == 0) {
        return make_tuple(0, 1);
    }
    
    int longitud_mitad = longitud_desplegado(n/2);

    if (r <= longitud_mitad) {
        return cantidad_unos_y_ceros(n/2, l, r);
    }

    if (l > longitud_mitad) {
        return cantidad_unos_y_ceros(n/2, l - longitud_mitad - 1, r - longitud_mitad - 1);
    }

    tuple<int, int> lado_izquierdo = cantidad_unos_y_ceros(n/2, l, longitud_mitad);
    tuple<int, int> lado_derecho = cantidad_unos_y_ceros(n/2, 0, r- longitud_mitad -1); 

    int ceros = get<1>(lado_izquierdo) + get<1>(lado_derecho);
    int unos = get<0>(lado_izquierdo) + get<0>(lado_derecho);

    tuple<int, int> result = make_tuple(unos, ceros);

    return result;
}

int main() {

    int n, l, r;
    cin >> n >> l >> r;

    tuple<int, int> unosYceros = cantidad_unos_y_ceros(n, l, r);
    int resultado = get<0>(unosYceros);

    cout << resultado << endl;
}