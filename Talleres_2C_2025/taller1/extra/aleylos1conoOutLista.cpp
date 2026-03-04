/*
ale tiene una lista de un solo elemento n. Debe realizaar ciertas operaciones y en cada una
debe eliminar algun elemento x, tal que x>1, e insertar en la misma posicion piso(x/2), x mod 2, piso(x/2)
secuencialmente
debe continuar con estas operaciones hasta que todos los elemtnso de la lista sean 0 o 1
quieren el numero total de 1 en el rango de l a r (indexado desde 1, inclye a l y a r)

el input contiene a n el elem de la lista, l y r (el rango)
r no es mayor que la longitud de la lista final
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> expandir(int n) {
    vector<int> n_expandido;

    if (n == 1 || n == 0) {
        n_expandido.push_back(n);
        return n_expandido;
    }
    
    vector<int> lista_Izq_Der = expandir(n/2);
    vector<int> mod_n;
    mod_n.push_back(n % 2);

    n_expandido.insert(n_expandido.end(), lista_Izq_Der.begin(), lista_Izq_Der.end());
    n_expandido.insert(n_expandido.end(), mod_n.begin(), mod_n.end()); 
    n_expandido.insert(n_expandido.end(), lista_Izq_Der.begin(), lista_Izq_Der.end()); 

    return n_expandido;
}

int ale_y_los1(int n, int l, int r) {
    int cantidad_unos = 0;

    vector<int> n_expandido = expandir(n);

    for (int i = l-1; i < r; i++) {
        if (n_expandido[i] == 1) {
            cantidad_unos++;
        } 
    }

    return cantidad_unos;
}

int main() {
    int n, l, r;
    cin >> n >> l >> r;

    vector<int> expandido = expandir(n);
    int resultado = ale_y_los1(n, l, r);

    for (int i = 0; i < expandido.size(); i++) {
            cout << expandido[i] << " ";
    }
    cout << endl;
    cout << resultado << endl;
}