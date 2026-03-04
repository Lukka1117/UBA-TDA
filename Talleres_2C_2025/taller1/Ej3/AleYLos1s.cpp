/*ale tiene una lista de un solo elemento n. Debe realizaar ciertas operaciones y en cada una
debe eliminar algun elemento x, tal que x>1, e insertar en la misma posicion piso(x/2), x mod 2, piso(x/2)
secuencialmente
debe continuar con estas operaciones hasta que todos los elemtnso de la lista sean 0 o 1
quieren el numero total de 1 en el rango de l a r (indexado desde 1, inclye a l y a r)

el input contiene a n el elem de la lista, l y r (el rango)
r no es mayor que la longitud de la lista final

se puede usar D&C porq quiero dividir el n en problemas mas chicos, y las divisiones son
siempre proporcionales, luego combino las soluciones

yo queria armar toda la lista primero y contar despues los 1 peroclaro con numeros mas grandes me usa un
monton de memoria y tiempo y no me pasa xdxd

cambiando de idea, hago algo parecido al problema de los subconjuntos que suman que hicimos en clase
por las operaciones que se le hacen a n, se puede saber el tamaño de la lista final porq siemore va a ser
la concatenacion de la lista que se arma expandiendo n/2 con n mod 2 y con la lista de n/2 nuevamente

y como me dan los indices del rango donde quiero contar los unos, sabiendo el tamaño de la lista final no
necesito armarla, uso de caso base que cuando el tam es 1, si el elemento es 0 la cantidad de 1 es 0, si el
elem es 1, la cantidad de 1 es 1. Despues separo en casos, cuando el rango de indices que me pasan estan solo en
el lado izquierdo de la lista, cuento los unos solo en esa mitad. Si el rango entra solo en el lado derecho, cuento los
unos en esa mitad. Y si el rango toma posiciones que incluyen el medio, calculo la cantidad de 1 del lado izq, la
cantidad de 1 del lado derecho, y n mod 2. Depsues esos 3 valores los sumo a la cantidad total de 1

ahora espero q si tarde menos y ocupe menos memoria jsjsj
se me estaba haciendo lio el tema de 1-based 0-based asi q cambie todo a 0-based porq me gusta mas
*/

#include <iostream>
using namespace std;

int n;
int limite_izq;
int limite_der;

void inputs() {

    cin >> n >> limite_izq >> limite_der;

}

//calcula la tamaño que tendria el n desplegado completamente como array
long long tam_expandido(int n) {
    if (n == 1 || n == 0) {
        return 1;
    } else {
        return (tam_expandido(n/2) * 2) + 1;
    }
}

int contr_unos(int n, long long l, long long r) {

    int cantidad_unos = 0;

    if (n == 0) {
        return 0;
    }
    if (n == 1) {
        return 1;
    }

    long long tam_lado_izq = tam_expandido(n/2);
    
    //si el limite derecho es menor a la posicion del medio, todos los 1 que quiero estan del lado izq
    if (r < tam_lado_izq) {
         return contr_unos(n/2, l, r);
    }
    
    long long posicion_medio = tam_lado_izq;
    //si el limite izq es mayor a la posicion del meido, todos los 1 que quiero estan del lado derecheo
    if (l > posicion_medio){
          return contr_unos(n/2, l - posicion_medio-1, r - posicion_medio-1);
    }

    //si el rango cruza el medio, le sumo al total los 1 del lado izq, el valor del medio (1 o 0), y los del lado izq
    if (l < tam_lado_izq) {
        cantidad_unos += contr_unos(n/2, l, tam_lado_izq);
    }

    if (l <= posicion_medio && posicion_medio <= r){
        cantidad_unos += (n % 2);
    }

    if (r > posicion_medio) {
        cantidad_unos += contr_unos(n/2, 0, r - posicion_medio-1);
    }

    return cantidad_unos;
}


int main() {
    inputs();

    int resultado = contr_unos(n, limite_izq-1, limite_der-1);

    cout << resultado << endl;
}