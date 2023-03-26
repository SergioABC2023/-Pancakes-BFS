#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

// Estructura que representa un estado del juego de pancakes
struct Estado {
    vector<char> pancakes;
    int costo; // cantidad de volteos realizados
    vector<int> camino; // lista de los índices de los pancakes volteados

    Estado(vector<char> p, int c, vector<int> cam) {
        pancakes = p;
        costo = c;
        camino = cam;
    }
};

// Función que imprime el camino de volteos de pancakes para llegar a la solución
void imprimir_camino(vector<int> camino) {
    for (int i = 0; i < camino.size(); i++) {
        cout << camino[i] << " ";
    }
    cout << endl;
}

// Función que verifica si el estado actual es la solución (pancakes ordenados de forma ascendente)
bool es_solucion(vector<char> pancakes) {
    vector<char> pancakes_ordenados = pancakes;
    sort(pancakes_ordenados.begin(), pancakes_ordenados.end());
    return pancakes == pancakes_ordenados;
}

// Función que realiza el volteo de los pancakes
void voltear_pancakes(vector<char>& pancakes, int desde, int hasta) {
    while (desde < hasta) {
        char temp = pancakes[desde];
        pancakes[desde] = pancakes[hasta];
        pancakes[hasta] = temp;
        desde++;
        hasta--;
    }
}

// Función que imprime el arreglo de pancakes
void imprimir_pancakes(vector<char> pancakes) {
    for (int i = 0; i < pancakes.size(); i++) {
        cout << pancakes[i] << " ";
    }
    cout << endl;
}

// Función que realiza la búsqueda en amplitud
void busqueda_en_amplitud(vector<char> pancakes) {
    queue<Estado> cola;
    Estado estado_inicial = Estado(pancakes, 0, {});
    cola.push(estado_inicial);

    while (!cola.empty()) {
        Estado estado_actual = cola.front();
        cola.pop();

        if (es_solucion(estado_actual.pancakes)) {
            cout << "Voltear pancakes: ";
            imprimir_camino(estado_actual.camino);
            cout << " "<< endl;
            cout << "Arreglo ordenado: ";
            imprimir_pancakes(estado_actual.pancakes);
            cout << " "<< endl;
            cout << "Nodos visitados: " << estado_actual.costo << endl;
            return;
        }

        // Funcion para generar sucesores
        for (int i = 2; i <= estado_actual.pancakes.size(); i++) {
            vector<char> pancakes_sucesor = estado_actual.pancakes;
            voltear_pancakes(pancakes_sucesor, 0, i - 1);
            Estado sucesor = Estado(pancakes_sucesor, estado_actual.costo + 1, estado_actual.camino);
            sucesor.camino.push_back(i);
            cola.push(sucesor);
        }
    }
}

// Función principal
int main() {
    string entrada;
    vector<char> pancakes;

    cout << "Pancakes con busqueda en amplitud ";
    cout << " "<< endl;
    cout << "Ingrese los caracteres a ordenar(letras) Ejemplo( flrpmend ) caracteres: ";
    getline(cin, entrada);
    istringstream iss(entrada);

    char c;
    while (iss >> c) {
        pancakes.push_back(c);
    }

    cout << "Arreglo de pancakes: ";
    imprimir_pancakes(pancakes);

    busqueda_en_amplitud(pancakes);
    return 0;
}
