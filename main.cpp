#include <iostream>
#include <cstdlib>
#include <ctime>
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

    // Inicializar la semilla para números aleatorios
    srand(time(0));

    int num_torres_bando1 = rand() % (filas / 5) + 1;
    int num_torres_bando2 = rand() % (filas / 5) + 1;

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < 4; j++) {
            // Verificar si la posición actual es una torre
            if ((i % 3 != 0 || i == 0) && (i % 3 != 2 || i == filas - 1)) {
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
            } else {
                // La posición actual es una torre
                if (num_torres_bando1 > 0 && j == 0) {
                    mapa[i][j][0] = 'T';  // Torre del bando 1
                    num_torres_bando1--;
                } else if (num_torres_bando2 > 0 && j == 3) {
                    mapa[i][j][0] = 't';  // Torre del bando 2
                    num_torres_bando2--;
                } else {
                    mapa[i][j][0] = ' ';  // Espacio entre torres
                }

                // Agregado el terminador nulo
                mapa[i][j][1] = '\0';

                cout << mapa[i][j];
            }
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
