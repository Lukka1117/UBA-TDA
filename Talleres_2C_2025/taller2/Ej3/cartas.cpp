/*
tenemos n jugadores, cada jugador j tiene un numero favorito de cartas f[j]
hay n*k cartas, la carta i contiene un entero c[i]
se le da k cartas a cada jugador, y un jugador i que recibe t cartas con su numero favorito f[i]
tiene alegria h[t], donde h[0] = 0
queremos la maxima suma posible de alegrias de los jugadores si se distribuyen las cartas de forma optima

de inputs tenemos:
2 enteros n y k (1≤n≤500, 1≤k≤10) El número de jugadores y la cantidad de cartas que cada jugador va a recibir.
La segunda línea contiene los n∗kenteros ci. (1≤ci≤105)
La tercera línea contiene los nenteros fi(1≤fi≤105)
La cuarta línea contiene los k enteros h1…hk(1≤hi≤105). Se garantiza que ht−1<htpara 2≤t≤k.

y de output: 
unico entero que representa la maxima alegria posible

cartas(jugador, favs_av) = maxima felicidad acumulada que se consigue repartiendole t cartas favoritas a cada jugador desde el jugador i
                            teniendo en cuenta la cantidad de cartas favoritas disponibles 

cartas(jugador, favs_av) = {0                                                                                si jugador >= n}
                           {max(felicidad[t] + cartas(jugador + 1, favs_av'))|0 <= t <= min(k, favs_av)|      sino}

la llamada inicial seria cartas(0, favs_av[0]), consiguiendo antes de llamar la cantidad de favoritas disponibles del primer jugador
la idea es tomar la cantidad disponible de cartas favoritas de un jugador, y probar todas las posibles cantidades de cartas
favoritas que se le puede dar, y para cada opcion calcular la felixidad del jugador y sumarle el resultado de repartir las cartas
a los proximos jugadores. De todas las opciones me quedo con el maximo 

cantidad de estados: tenemos n jugadores, y la cantidad de cartas favoritas puedellegar a ser todo el conjunto de cartas, o sea n*k
                    --> O(n^2*k)
                    Y en transiciones por estado, por cada estado puedo ver hasta k casos (cantidad de cartas q recibe cada jugador)
                    --> O(n^2*k^2)
cantidad de llamados rec: cada jugador puede recibir entre 0 a k cartas favoritas, en el peor caso hay k+1 llamados por jugador
                        --> O(k+1)^n

como la cantidad de llamados rec es exponencial y la cant de estados polinomial, podria decir que en general
O(k+1)^n >> O(n^2*k^2)

bueno al final asi no pasa porq estoy guardando mal en la memoria jskjs pero fue voy a ver si pasa el codeforces si se la saco
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

#define NEG -10000000

//long long memo[500][5000];

int jugadores;
int cartas_x_jugador;
vector<int> lista_cartas;
vector<int> favoitas;
vector<int> felicidad_x_cantidad;
vector<int> cantidad_x_numero;
int cartas_totales;

void inputs() {

    cin >> jugadores >> cartas_x_jugador;
    cartas_totales = jugadores * cartas_x_jugador;
    
    lista_cartas.resize(cartas_totales);
    favoitas.resize(jugadores);
    felicidad_x_cantidad.assign(cartas_x_jugador + 1, 0);
    cantidad_x_numero.assign(1000001, 0);

    for (int i = 0; i < cartas_totales; i++) {
        cin >> lista_cartas[i];
    }

    for (int i = 0; i < jugadores; i++) {
        cin >> favoitas[i];
    }

    for (int i = 1; i <= cartas_x_jugador; i++) {
        cin >> felicidad_x_cantidad[i];
    }

    for (int i = 0; i < lista_cartas.size(); i++) {
            int num = lista_cartas[i];
            cantidad_x_numero[num]++;
    }

}

int cartas(int jugador){
    
 //ya reparti a todos los jugadores
    if (jugador >= jugadores) {
        return 0;
    }

    int max_alegria = NEG;
    int fav_jugador = favoitas[jugador];
    int favs_disponibles = cantidad_x_numero[fav_jugador];

   /* if (memo[jugador][favs_disponibles] != -1) {
        return memo[jugador][favs_disponibles];
    }*/

    for (int t = 0; t <= min(cartas_x_jugador, favs_disponibles); t++) {
        cantidad_x_numero[fav_jugador] -= t;
        int alegria = felicidad_x_cantidad[t] + cartas(jugador + 1);
        max_alegria = max(max_alegria, alegria);
        cantidad_x_numero[fav_jugador] += t;
    } 

    //memo[jugador][favs_disponibles] = max_alegria;

    return max_alegria; 
}

int main() {
    inputs();
   // memset(memo, -1, sizeof(memo));

    int resultado = cartas(0);

    cout << resultado << endl;
}