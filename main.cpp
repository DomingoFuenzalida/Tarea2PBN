#include <iostream>
#include "personaje.h"
#include <cstdlib>
using namespace std;
void gen_personajes(char**);



int main(){
    int cantidad_filas;
    cout << "ingrese la cantidad de filas (15 ~ 40): ";
    cin >> cantidad_filas;
    char static mapa[cantidad_filas][4];

    mapa = malloc(sizeof(char*) * 4);
    for (int i = 0 ; i < cantidad_filas; i++){
        mapa[i] = malloc(sizeof(char*) * 4);
    }
    gen_personajes
    for (int i = 0; i < 9; i++) {
	free(mapa[i]);}
	free(mapa);
	return 0;
    
}

void gen_personajes(){


}

// Soldado 30%
// Arquero 15%
// Caballero 20%
// Zombie 10%
// Sin personaje 25%