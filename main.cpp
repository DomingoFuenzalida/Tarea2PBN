#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

void gen_personajes(char***& mapa, int filas);
void imprimir_mapa(char*** mapa, int filas);
void liberar_memoria(char***& mapa, int filas);

int main() {
    int cantidad_filas;
    cout << "Ingrese la cantidad de filas (15 ~ 40): ";
    cin >> cantidad_filas;

    char*** mapa;
    gen_personajes(mapa, cantidad_filas);

    // Imprimir el mapa
    imprimir_mapa(mapa, cantidad_filas);

    liberar_memoria(mapa, cantidad_filas);
    return 0;
}

void gen_personajes(char***& mapa, int filas) {
    mapa = (char***)malloc(sizeof(char**) * filas);

    for (int i = 0; i < filas; i++) {
        mapa[i] = (char**)malloc(sizeof(char*) * 4);
        for (int j = 0; j < 4; j++) {
            mapa[i][j] = (char*)malloc(sizeof(char) * 2);
            mapa[i][j][0] = ' ';
            mapa[i][j][1] = '\0';
        }
    }

    // Inicializar la semilla para números aleatorios
    srand(time(0));

    int num_torres_bando1 = rand() % (filas / 5) + 1;
    int num_torres_bando2 = rand() % (filas / 5) + 1;

    for (int i = 0; i < num_torres_bando1; ++i) {
        int posicion;

        do {
            // Generar una posición aleatoria para la torre
            posicion = rand() % filas;

            // Verificar si la posición cumple con la condición de distancia
            bool distanciaAceptable = true;
            for (int j = 0; j < filas; ++j) {
                if (mapa[j][1][0] == 'T' && abs(j - posicion) < 4) {
                    distanciaAceptable = false;
                    break;
                }
            }

            if (distanciaAceptable) {
                break;
            }
        } while (true);

        // Colocar la torre en la posición generada
        mapa[posicion][1][0] = 'T';
    }

    for (int i = 0; i < num_torres_bando2; ++i) {
        int posicion;

        do {
            // Generar una posición aleatoria para la torre
            posicion = rand() % filas;

            // Verificar si la posición cumple con la condición de distancia
            bool distanciaAceptable = true;
            for (int j = 0; j < filas; ++j) {
                if (mapa[j][2][0] == 'T' && abs(j - posicion) < 4) {
                    distanciaAceptable = false;
                    break;
                }
            }

            if (distanciaAceptable) {
                break;
            }
        } while (true);

        // Colocar la torre en la posición generada
        mapa[posicion][2][0] = 'T';
    }

    // Obtener posiciones vacías en las columnas 0 y 3
    vector<pair<int, int>> posiciones_vacias;
    for (int i = 0; i < filas; i++) {
        if (mapa[i][0][0] == ' ' && mapa[i][3][0] == ' ') {
            posiciones_vacias.push_back({i, 0});
            posiciones_vacias.push_back({i, 3});
        }
    }

    // Número de ingenieros por cada bando
    int ingenieros_1 = num_torres_bando1 / 2;  // Puedes ajustar esto según tus necesidades

    for (int i = 0; i < ingenieros_1 && !posiciones_vacias.empty(); ++i) {
        // Elegir aleatoriamente una posición vacía
        int indice = rand() % posiciones_vacias.size();
        int fila = posiciones_vacias[indice].first;

        // Colocar el ingeniero en la posición elegida
        mapa[fila][0][0] = 'I';

        // Eliminar la posición utilizada de las posiciones vacías
        posiciones_vacias.erase(posiciones_vacias.begin() + indice);
    }

    int ingenieros_2 = num_torres_bando2 / 2;  // Puedes ajustar esto según tus necesidades

    for (int i = 0; i < ingenieros_2 && !posiciones_vacias.empty(); ++i) {
        // Elegir aleatoriamente una posición vacía
        int indice = rand() % posiciones_vacias.size();
        int fila = posiciones_vacias[indice].first;

        // Colocar el ingeniero en la posición elegida
        mapa[fila][3][0] = 'I';

        // Eliminar la posición utilizada de las posiciones vacías
        posiciones_vacias.erase(posiciones_vacias.begin() + indice);
    }

    
// Número de héroes por cada bando
int heroes_1 = 1;  // Un héroe por bando
for (int i = 0; i < heroes_1 && !posiciones_vacias.empty(); ++i) {
    // Elegir aleatoriamente una posición vacía
    int indice = rand() % posiciones_vacias.size();
    int fila = posiciones_vacias[indice].first;

    // Colocar el héroe en la posición elegida
    mapa[fila][1][0] = 'H';

    // Eliminar la posición utilizada de las posiciones vacías
    posiciones_vacias.erase(posiciones_vacias.begin() + indice);
}

int heroes_2 = 1;  // Un héroe por bando
for (int i = 0; i < heroes_2 && !posiciones_vacias.empty(); ++i) {
    // Elegir aleatoriamente una posición vacía
    int indice = rand() % posiciones_vacias.size();
    int fila = posiciones_vacias[indice].first;

    // Colocar el héroe en la posición elegida
    mapa[fila][2][0] = 'H';

    // Eliminar la posición utilizada de las posiciones vacías
    posiciones_vacias.erase(posiciones_vacias.begin() + indice);
}

// Probabilidades de aparición de personajes en celdas vacías
for (int i = 0; i < filas; ++i) {
        if (mapa[i][1][0] == ' ') {
            int probabilidad = rand() % 100 + 1;  // Número aleatorio entre 1 y 100

            if (probabilidad <= 30) {
                mapa[i][1][0] = 'S';  // Soldado con probabilidad del 30%
            } else if (probabilidad <= 45) {
                mapa[i][1][0] = 'A';  // Arquero con probabilidad del 15%
            } else if (probabilidad <= 65) {
                mapa[i][1][0] = 'C';  // Caballero con probabilidad del 20%
            } else if (probabilidad <= 75) {
                mapa[i][1][0] = 'Z';  // Zombie con probabilidad del 10%
            } else {
                // Sin personaje con probabilidad del 25%
            }
        }
    }

for (int i = 0; i < filas; ++i) {
        if (mapa[i][2][0] == ' ') {
            int probabilidad = rand() % 100 + 1;  // Número aleatorio entre 1 y 100

            if (probabilidad <= 30) {
                mapa[i][2][0] = 'S';  // Soldado con probabilidad del 30%
            } else if (probabilidad <= 45) {
                mapa[i][2][0] = 'A';  // Arquero con probabilidad del 15%
            } else if (probabilidad <= 65) {
                mapa[i][2][0] = 'C';  // Caballero con probabilidad del 20%
            } else if (probabilidad <= 75) {
                mapa[i][2][0] = 'Z';  // Zombie con probabilidad del 10%
            } else {
                // Sin personaje con probabilidad del 25%
            }
        }
    }

int contador_no_medicos_bando1 = 0;
int contador_no_medicos_bando2 = 0;
// Generar médicos en el bando 1 (columna 0)
for (int i = 0; i < filas; ++i) {
    if (mapa[i][0][0] != 'T' && mapa[i][0][0] != 'M' && mapa[i][0][0] != ' ') {
        contador_no_medicos_bando1++;
    }
    if (mapa[i][1][0] != 'T' && mapa[i][1][0] != 'M' && mapa[i][1][0] != ' ') {
        contador_no_medicos_bando1++;
    }
}

// Generar médicos en el bando 2 (columna 3)
for (int i = 0; i < filas; ++i) {
    if (mapa[i][2][0] != 'T' && mapa[i][2][0] != 'M' && mapa[i][2][0] != ' ') {
        contador_no_medicos_bando2++;
    }
    if (mapa[i][3][0] != 'T' && mapa[i][3][0] != 'M' && mapa[i][3][0] != ' ') {
        contador_no_medicos_bando2++;
    }
}
for (int i = 0; i < contador_no_medicos_bando1/5; i++){
    int posicion = rand() % filas;
    if (mapa[posicion][0][0] != ' '){
        i--;
    }
    else{
        mapa[posicion][0][0] = 'M';
    }

}
for (int i = 0; i < contador_no_medicos_bando2/5; i++){
    int posicion = rand() % filas;
    if (mapa[posicion][3][0] != ' '){
        i--;
    }
    else{
        mapa[posicion][3][0] = 'M';
    }

}

}


void imprimir_mapa(char*** mapa, int filas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < 4; j++) {
            cout << mapa[i][j][0] << " ";
        }
        cout << endl;
    }
}

void liberar_memoria(char***& mapa, int filas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < 4; j++) {
            free(mapa[i][j]);
        }
        free(mapa[i]);
    }
    free(mapa);
}



