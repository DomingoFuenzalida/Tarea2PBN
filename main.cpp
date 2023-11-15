#include <iostream>
#include "personaje.h"
#include <cstdlib>
using namespace std;
void gen_personajes(int filas);



int main(){
    int cantidad_filas;
    cout << "ingrese la cantidad de filas (15 ~ 40): ";
    cin >> cantidad_filas;
    char static mapa[cantidad_filas][4];
    gen_personajes(cantidad_filas);

    for (int i = 0; i < 9; i++) {
	free(mapa[i]);}
	free(mapa);
	return 0;
    
}

void gen_personajes(filas){
    mapa = malloc(sizeof(char*) * 4);
    for (int i = 0 ; i < filas; i++){
        mapa[i] = malloc(sizeof(char*) * 4);
    }


}

// Soldado 30%
// Arquero 15%
// Caballero 20%
// Zombie 10%
// Sin personaje 25%