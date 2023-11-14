#include <iostream>
#include "personaje.h"

using namespace std;

personaje::personaje(char codigo, int salud_base, int equipo, int pos_x, int pos_y) {
    this->codigo = codigo;
    this->salud_base = salud_base;
    this->equipo = equipo;
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

void personaje::desplazarse(int objetivo) {
    // Implementación del desplazamiento
}

void personaje::actuar(char objetivo, char accion) {
    // Implementación de la acción
}
