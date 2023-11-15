#include <iostream>
#include <cstdlib>
#include <ctime>

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
                if (mapa[j][0][0] == 'T' && abs(j - posicion) < 4) {
                    distanciaAceptable = false;
                    break;
                }
            }

            if (distanciaAceptable) {
                break;
            }
        } while (true);

        // Colocar la torre en la posición generada
        mapa[posicion][0][0] = 'T';
    }

    for (int i = 0; i < num_torres_bando2; ++i) {
        int posicion;

        do {
            // Generar una posición aleatoria para la torre
            posicion = rand() % filas;

            // Verificar si la posición cumple con la condición de distancia
            bool distanciaAceptable = true;
            for (int j = 0; j < filas; ++j) {
                if (mapa[j][3][0] == 'T' && abs(j - posicion) < 4) {
                    distanciaAceptable = false;
                    break;
                }
            }

            if (distanciaAceptable) {
                break;
            }
        } while (true);

        // Colocar la torre en la posición generada
        mapa[posicion][3][0] = 'T';
    }
    // Puedes agregar un bucle similar para las torres del bando 2
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
