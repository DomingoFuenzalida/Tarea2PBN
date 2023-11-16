#ifndef MEDICO_H
#define MEDICO_H

#include "personaje.h"

class Medico : public Personaje {
public:
    Medico(string code, int x, int y, string team);
};

#endif

