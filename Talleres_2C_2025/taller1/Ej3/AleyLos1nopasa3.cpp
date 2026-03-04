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

no me habia dado los tiempos en un test asi que pruebo guardando el valor de n/2 en vez de calcularlo
en cada llamado a recursion, y asigno antes la longitud del vector para que no me copie todo el vector
cada vez que inserta un elem. No me habia dado cuenta q estaba usando memoria y tiempo de mas en eso

todavia no pasaba los tiempos, asi que ahora que vimos DP puedo probar con una memoria que me guarde
las listas expandidas que le corresponde a cada numero, asi cuando lo necesito de vuelta no lo tiene que 
volver a calcular
lo defino como un diccionario donde la key es el numero y el valor la lista que le corresponde
luego si el n ya esta en el dicc, devuelve esa lista en lugar ded calcular todo de vuelta
espero que ahora tarde menos xd

bueno tuve que cambiar todo porq no me di cuenta q lo q se iba al carajo era la memoria jajan't
(claro la porfiada queria seguir armando la lista completa)

*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;

unordered_map<long long, vector<long long>> ya_calculados;

//expande n a una lista recursivamente con las operaciones q me pide
const vector<long long>& expandir(long long n) {

    if (ya_calculados.find(n) != ya_calculados.end()) {
        return ya_calculados[n];
    }

    vector<long long> n_expandido;

    if (n == 1 || n == 0) {
        n_expandido.push_back(n);
        
        return ya_calculados[n] = move(n_expandido);
    }
    
    long long mitad = n / 2;
    const vector<long long>& mitad_expandida = expandir(mitad);
    long long mod_n = n % 2;

    n_expandido.reserve((mitad_expandida.size() * 2) + 1);

    n_expandido.insert(n_expandido.end(), mitad_expandida.begin(), mitad_expandida.end());
    n_expandido.push_back(mod_n); 
    n_expandido.insert(n_expandido.end(), mitad_expandida.begin(), mitad_expandida.end());

    

    return  ya_calculados[n] = move(n_expandido);
}

//cuenta cuantos 1 hay en el rango entre l y r, en una lista que resulta de expandir n
long long ale_y_los1(int n, int l, int r) {

    long long cantidad_unos = 0;

    vector<long long> n_expandido = expandir(n);

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

    long long resultado = ale_y_los1(n, l, r);

    cout << resultado << endl;
}