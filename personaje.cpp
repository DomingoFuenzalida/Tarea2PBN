#include "personaje.h"
#include <vector>
using namespace std;

void Personaje::stats_personajes(string code, int x, int y, string t) {
    codigo = code;
    posx = x;
    posy = y;
    team = t;
    if (codigo.compare("S") == 0) {
        nombre = "soldado";
        salud_base = 50;
        fuerza_max = 10;
        alcance_max = 1;
        direccion_ataque = "HV";
        desplazamiento = 1;
        curacion = 0;
        salud = 50;
    } else if (codigo.compare("A") == 0) {
        nombre = "arquero";
        salud_base  = 50;
        fuerza_max = 5;
        alcance_max = 3;
        direccion_ataque = "HVD";
        desplazamiento = 1;
        curacion = 0;
        salud = 50;
    } else if (codigo.compare("C") == 0) {
        nombre = "caballero";
        salud_base = 100;
        fuerza_max = 30;
        alcance_max = 1;
        direccion_ataque = "HV";
        desplazamiento = 3;
        curacion = 0;
        salud = 100;
    } else if (codigo.compare("T") == 0) {
        nombre = "torre";
        salud_base = 500;
        fuerza_max = 30;
        alcance_max = 3;
        direccion_ataque = "HVD";
        desplazamiento = 0;
        curacion = 0;
        salud = 500;
    } else if (codigo.compare("H") == 0) {
        nombre = "heroe";
        salud_base = 500;
        fuerza_max = 30;
        alcance_max = 1;
        direccion_ataque = "HVD";
        desplazamiento = 4;
        curacion = 5;
        salud = 500;
    } else if (codigo.compare("Z") == 0) {
        nombre = "zombie";
        salud_base = 50;
        fuerza_max = 10;
        alcance_max = 1;
        direccion_ataque = "HVD";
        desplazamiento = 1;
        curacion = 0;
        salud = 50;
    } else {
        nombre = " ";
        salud_base = 0;
        fuerza_max = 0;
        alcance_max = 0;
        direccion_ataque = "";
        desplazamiento = 0;
        curacion = 0;
        salud = 0;
    }
} 
void Personaje::actuar(Personaje& target){
    if(target.team != team && target.team != " "){
    int damage = rand() % (fuerza_max - fuerza_max / 2 + 1) + fuerza_max / 2;
    target.salud -= damage;
    if (target.salud <= 0){
        target.codigo = " ";
        target.salud_base = 0;
        target.fuerza_max = 0;
        target.alcance_max = 0;
        target.direccion_ataque = "";
        target.desplazamiento = 0;
        target.curacion = 0;
        target.team = " ";
        target.salud = 0;       
    }}
    if (target.codigo != "T" and target.team == team && codigo == "M"){
        int cu = rand() % (curacion - curacion / 2 + 1) + curacion / 2;    
        target.salud += cu;
    if (target.salud > target.salud_base){
        target.salud = target.salud_base;
    }}
    if (target.codigo == "T" and target.team == team && codigo == "I"){
    int cu = rand() % (curacion - curacion / 2 + 1) + curacion / 2;
    target.salud += cu;
    if (target.salud > target.salud_base){
        target.salud = target.salud_base;
    }}
}
void Personaje::desplazarse(int target, vector<Personaje>& personajes, int origen){
    swap(personajes[origen], personajes[target]);
}