#include <iostream>
#include <cstdlib>
using namespace std;

void gen_personajes(char***& mapa, int filas);
void liberar_memoria(char***& mapa, int filas);

int main() {
    int cantidad_filas;
    cout << "Ingrese la cantidad de filas (15 ~ 40): ";
    cin >> cantidad_filas;

    char*** mapa;
    gen_personajes(mapa, cantidad_filas);

    // Hacer algo con el mapa si es necesario

    liberar_memoria(mapa, cantidad_filas);
    return 0;
}

void gen_personajes(char***& mapa, int filas) {
    mapa = (char***)malloc(sizeof(char**) * filas);

    for (int i = 0; i < filas; i++) {
        mapa[i] = (char**)malloc(sizeof(char*) * 4);
        for (int j = 0; j < 4; j++) {
            mapa[i][j] = (char*)malloc(sizeof(char) * 2);  // Cambiado el tamaño a 2 para el carácter y el terminador nulo
        }
    }

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < 4; j++) {
            int numero_aleatorio = rand() % 100;

            if (numero_aleatorio < 30) {
                mapa[i][j][0] = 'S';
            } else if (numero_aleatorio >= 30 && numero_aleatorio < 45) {
                mapa[i][j][0] = 'A';
            } else if (numero_aleatorio >= 45 && numero_aleatorio < 65) {
                mapa[i][j][0] = 'C';
            } else if (numero_aleatorio >= 65 && numero_aleatorio < 75) {
                mapa[i][j][0] = 'Z';
            } else if (numero_aleatorio >= 75 && numero_aleatorio < 100) {
                mapa[i][j][0] = ' ';
            }

            // Agregado el terminador nulo
            mapa[i][j][1] = '\0';

            cout << mapa[i][j];
        }
        cout << "\n";
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


// Soldado 30%
// Arquero 15%
// Caballero 20%
// Zombie 10%
// Sin personaje 25%