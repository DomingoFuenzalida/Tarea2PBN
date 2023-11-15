#include "ingeniero.h"

Ingeniero::Ingeniero(string code, int x, int y) {
    stats_personajes(code, x, y);
    nombre = "soldado";
    salud_base = 30;
    fuerza_max = 50;
    alcance_max = 4;
    direccion_ataque = "HV";
    desplazamiento = 3;
    curacion = 20;
}