#include <iostream>
#include "personaje.h"

using namespace std;

personaje::personaje(char codigo,string tipo,int salud_base, int fuerza_max, int alcance_max, string direccion_ataque, int desplazamiento_max, int curacion) {
    codigo = codigo;
    tipo = tipo;
    salud_base = salud_base;
    fuerza_max = fuerza_max;
    alcance_max = alcance_max;
    direccion_ataque = direccion_ataque;
    desplazamiento_max = desplazamiento_max;
    curacion = curacion;
}

personaje::~personaje(){}

void personaje::desplazarse(int objetivo) {
    cout << objetivo;
}

void personaje::actuar(char objetivo, char accion) {
    cout << objetivo;
    cout << accion;
}
