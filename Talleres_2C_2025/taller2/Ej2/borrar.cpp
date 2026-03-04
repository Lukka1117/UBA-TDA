/*tengo un string s de n letras, al que se le puede aplicar la siguiente operacion:
elige un substring contiguo de caracteres iguales y lo borra, luego conctanea las partes restantes

inputs:
La primera línea contiene un entero n=|s| (1≤n≤500).
La segunda línea contiene el string s
outputs:
Imprime un único entero, la mínima cantidad de operaciones necesaria para borrar s

pense la funcion como:
borrar(inicio, fin): minima cantidad de elimminacioness que necesito para eliminar el substring entre los indice inicio y fin

borrar(inicion, fin) = {1                                                        si in = fin}
                      {min(borrar(in, fin), borrar(in, k) + borrar(k+1, fin))      si in < fin & pt k. in <= k < fin}
                      {min(borrar(in, fin), borrar(in+1, k-1) + borrar(k, fin))      si in < fin & pt k. in < k <= fin & str[in] = str[k]} 

si inicio y fin son ifuales, es una sola letra asi que elimina 1 
una opcion es mirar de a prefijos, quiero ver que pasa si tomo k como corte entre inicio y fin-1 y 
elimino desde i hasta (k-1) + eliminar desde k hasta n
la otra es, asumiendo que tengo 2 char iguales y k esta entre inicio +1 y fin, si str[i] = str[k], lo del medio puede
o ser todo el mismo caracter tmb o puede tener eliminaciones extras y despues concatenarse. 
Entonces elimino desde inicio+1 hasta k-1 ignorando el primero. Despues le sumo las eliminaciones desde k hasta fin, que eventualmente
va a contar la eliminacion de str[k], o se auqe cuenta tmb la del str[inicio] que se habia ignorado. (este solo funca cuando hay chars iguales)

de llamado inicial haho borrar(inicio, fin) porque quiero borrar todo el string, necesito que abarque todas las letras

estados: tenemos 1 string con n caracteres, y n posibles eliminaciones. Llenar la matriz memo cuesta O(n^2)
y para cada esatdo recorre k de inicio a fin en los dos for, o sea O(n). --> O(n^3)
llamadas recursivas: para una palabra de n letras se pueden hacer n-1 particiones y c/una llama a 2 subproblemas (genera hatsa 2(n-1) llam),
si todas las letras son iguales tmb genera esas particiones y cada una llama a 2 sbproblemas (lo mismo). Entonces el
factor de rammificacion es b(n) = 4(n-1) (no es constante). y la profundidad del arbol de recusrion es n porq en cada paso reducimos el segmento
Por lo que en el peor caso quedan aprox Ω(4^n) llamados recursivos

la complejidad total usando memo es O(n^3), no es lo mas lindo pero mejor que la exponencial es xd
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define MAX 500

int memo[500][500];

string palabra;
int n;

void inputs() {
    
    cin >> n >> palabra;

    memset(memo, -1, sizeof(memo));
}

int borrar (int inicio, int fin) {
    int resultado = MAX;

    if (inicio == fin) {
        return 1;
    }

    if (memo[inicio][fin] != -1) {
        return memo[inicio][fin];
    }

    for (int k = inicio; k < fin; k++) {
        int posibeRes = borrar(inicio, k) + borrar(k+1, fin);
        resultado = min(resultado, posibeRes);
    }

    for (int k = inicio+1; k <= fin; k++) {
        if (palabra[inicio] == palabra[k]) {
            int operaciones_medias = 0;
            if (inicio+1 <= k-1) {
                operaciones_medias = borrar(inicio+1, k-1);
            }
            int posibeRes2 = operaciones_medias + borrar(k, fin);
            resultado = min(resultado, posibeRes2);
        }
    }

    memo[inicio][fin] = resultado;
    return resultado;
}

int main () {
    inputs();

    int res = borrar(0, n-1);
    cout << res << endl;

    return 0;
}