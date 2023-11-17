#ifndef PERSONAJE_H
#define PERSONAJE_H

#include <iostream>
#include <string>
using namespace std;

class Personaje {
public:
    string codigo;
    string nombre;
    int salud_base;
    int fuerza_max;
    int alcance_max;
    string direccion_ataque;
    int desplazamiento;
    int curacion;
    int posx;
    int posy;
    string team;
    int salud;
    void stats_personajes(string, int, int, string);
    virtual void actuar(Personaje& target);
};

#endif


