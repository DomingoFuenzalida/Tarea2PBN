#include "personaje.h"
using namespace std;

void Personaje::stats_personajes(string code, int x, int y) {
    codigo = code;
    posx = x;
    posy = y;
    if (codigo.compare("S") == 0) {
        nombre = "soldado";
        salud_base = 50;
        fuerza_max = 10;
        alcance_max = 1;
        direccion_ataque = "HV";
        desplazamiento = 1;
        curacion = 0;
    } else if (codigo.compare("A") == 0) {
        nombre = "arquero";
        salud_base  = 50;
        fuerza_max = 5;
        alcance_max = 3;
        direccion_ataque = "HVD";
        desplazamiento = 1;
        curacion = 0;
    } else if (codigo.compare("C") == 0) {
        nombre = "caballero";
        salud_base = 100;
        fuerza_max = 30;
        alcance_max = 1;
        direccion_ataque = "HV";
        desplazamiento = 3;
        curacion = 0;
    } else if (codigo.compare("T") == 0) {
        nombre = "torre";
        salud_base = 500;
        fuerza_max = 30;
        alcance_max = 3;
        direccion_ataque = "HVD";
        desplazamiento = 0;
        curacion = 0;
    } else if (codigo.compare("H") == 0) {
        nombre = "heroe";
        salud_base = 500;
        fuerza_max = 30;
        alcance_max = 1;
        direccion_ataque = "HVD";
        desplazamiento = 4;
        curacion = 5;
    } else if (codigo.compare("Z") == 0) {
        nombre = "zombie";
        salud_base = 50;
        fuerza_max = 10;
        alcance_max = 1;
        direccion_ataque = "HVD";
        desplazamiento = 1;
        curacion = 0;
    } else {
        nombre = ' ';
        salud_base = 0;
        fuerza_max = 0;
        alcance_max = 0;
        direccion_ataque = "";
        desplazamiento = 0;
        curacion = 0;
    }
} 
