#include "ingeniero.h"

Ingeniero::Ingeniero(string code, int x, int y, string team) {
    stats_personajes(code, x, y, team);
    nombre = "Ingeniero";  // Cambiado de "soldado" a "Ingeniero"
    salud_base = 30;
    fuerza_max = 50;
    alcance_max = 4;
    direccion_ataque = "HV";
    desplazamiento = 3;
    curacion = 20;
    team = team;
    salud = 30;
}
void Ingeniero::actuar(Personaje& target){
    if (target.codigo != "T" and target.team == team && codigo == "M"){
        int cu = rand() % (curacion - curacion / 2 + 1) + curacion / 2;    
        target.salud += cu;
    if (target.salud > target.salud_base){
        target.salud = target.salud_base;
    }}}