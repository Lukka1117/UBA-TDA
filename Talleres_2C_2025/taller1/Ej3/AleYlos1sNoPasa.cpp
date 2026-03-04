/*
ale tiene una lista de un solo elemento n. Debe realizaar ciertas operaciones y en cada una
debe eliminar algun elemento x, tal que x>1, e insertar en la misma posicion piso(x/2), x mod 2, piso(x/2)
secuencialmente
debe continuar con estas operaciones hasta que todos los elemtnso de la lista sean 0 o 1
quieren el numero total de 1 en el rango de l a r (indexado desde 1, inclye a l y a r)

el input contiene a n el elem de la lista, l y r (el rango)
r no es mayor que la longitud de la lista final

se puede usar D&C porq quiero dividir el n en problemas mas chicos, y las divisiones son
siempre proporcionales, luego combino las soluciones
voy a querer primero expandir el n que me pasan y despues calcular cuantos 1 tiene en el rango que piden
para expandirlo, si n es 0 o 1 devuelve [0] o [1]
si n > 1, quiero conseguir recursivamente la expansion de n/2, y calcular n mod 2
luego hacer la concatenacion de la expancion tipo: expansion de n/2 ++ [n mod 2] ++ expansion de n/2
y esa es la lista final a la que quiero contar la cantidad de 1's en el rango pasado por input
los cuento de forma lineal 
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

//expande n a una lista recursivamente con las operaciones q me pide
vector<int> expandir(int n) {

    vector<int> n_expandido;

    if (n == 1 || n == 0) {
        n_expandido.push_back(n);
        return n_expandido;
    }
    
    vector<int> mitad_expandida = expandir(n/2);
    int mod_n = n % 2;

    n_expandido.insert(n_expandido.end(), mitad_expandida.begin(), mitad_expandida.end());
    n_expandido.insert(n_expandido.end(), mod_n); 
    n_expandido.insert(n_expandido.end(), mitad_expandida.begin(), mitad_expandida.end()); 

    return n_expandido;
}

//cuenta cuantos 1 hay en el rango entre l y r, en una lista que resulta de expandir n
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

    int resultado = ale_y_los1(n, l, r);

    cout << resultado << endl;
}