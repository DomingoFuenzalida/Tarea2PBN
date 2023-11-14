#ifndef PERSONAJE_H
#define PERSONAJE_H

class personaje {
public:
    char codigo;
    int salud_base;
    int equipo;
    int pos_x;
    int pos_y;

    personaje(char codigo, int salud_base, int equipo, int pos_x, int pos_y);
    void desplazarse(int objetivo);
    void actuar(char objetivo, char accion);
};

#endif
