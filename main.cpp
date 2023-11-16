#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <chrono>
#include <thread>
#include "ingeniero.h"
#include "medico.h"
#include "personaje.h"
using namespace std;
void crear_personajes(char***& mapa, int filas);
void gen_personajes(char***& mapa, int filas);
void imprimir_mapa(const vector<Personaje>& personajes, int filas);
void liberar_memoria(char***& mapa, int filas);
void atacar(vector<Personaje>& personajes);
int main() {
    int cantidad_filas;
    cout << "Ingrese la cantidad de filas (15 ~ 40): ";
    cin >> cantidad_filas;

    char*** mapa;
    gen_personajes(mapa, cantidad_filas);
    
    vector<Personaje> personajes;
    for (int i = 0; i < cantidad_filas; ++i) {
        for (int j = 0; j < 4; ++j) {
            
                Personaje nuevo_personaje;
                if (mapa[i][j][0] == 'I') {
                    if (j < 2){
                    Ingeniero ingeniero(mapa[i][j], j, i, "O");
                    personajes.push_back(ingeniero);}
                    else {
                    Ingeniero ingeniero(mapa[i][j], j, i, "E");
                    personajes.push_back(ingeniero);                        
                    }
                } else if (mapa[i][j][0] == 'M') {
                    if (j < 2){
                    Medico medico(mapa[i][j], j, i, "O");
                    personajes.push_back(medico);}
                    else{
                    Medico medico(mapa[i][j], j, i, "E");
                    personajes.push_back(medico);                        
                    }
                } else {
                    if (j < 2){
                    nuevo_personaje.stats_personajes(mapa[i][j], j, i, "O");
                    personajes.push_back(nuevo_personaje);}
                    else{
                    nuevo_personaje.stats_personajes(mapa[i][j], j, i, "E");
                    personajes.push_back(nuevo_personaje);                        
                    }
                }
            
        }
    }
    
    
    // Imprimir el mapa
    imprimir_mapa(personajes, cantidad_filas);
    this_thread::sleep_for(chrono::milliseconds(1000));
    atacar(personajes);
    this_thread::sleep_for(chrono::milliseconds(1000));
    imprimir_mapa(personajes, cantidad_filas);
    this_thread::sleep_for(chrono::milliseconds(1000));
    atacar(personajes);
    this_thread::sleep_for(chrono::milliseconds(1000));
    imprimir_mapa(personajes, cantidad_filas);
    this_thread::sleep_for(chrono::milliseconds(1000));
    liberar_memoria(mapa, cantidad_filas);
    return 0;
}

void gen_personajes(char***& mapa, int filas) {
    mapa = (char***)malloc(sizeof(char**) * filas);

    for (int i = 0; i < filas; i++) {
        mapa[i] = (char**)malloc(sizeof(char*) * 4);
        for (int j = 0; j < 4; j++) {
            mapa[i][j] = (char*)malloc(sizeof(char) * 2);
            mapa[i][j][0] = ' ';
            mapa[i][j][1] = '\0';
        }
    }

    // Inicializar la semilla para números aleatorios
    srand(time(0));

    int num_torres_bando1 = rand() % (filas / 5) + 1;
    int num_torres_bando2 = rand() % (filas / 5) + 1;

    for (int i = 0; i < num_torres_bando1; ++i) {
        int posicion;

        do {
            // Generar una posición aleatoria para la torre
            posicion = rand() % filas;

            // Verificar si la posición cumple con la condición de distancia
            bool distanciaAceptable = true;
            for (int j = 0; j < filas; ++j) {
                if (mapa[j][1][0] == 'T' && abs(j - posicion) < 4) {
                    distanciaAceptable = false;
                    break;
                }
            }

            if (distanciaAceptable) {
                break;
            }
        } while (true);

        // Colocar la torre en la posición generada
        mapa[posicion][1][0] = 'T';
    }

    for (int i = 0; i < num_torres_bando2; ++i) {
        int posicion;

        do {
            // Generar una posición aleatoria para la torre
            posicion = rand() % filas;

            // Verificar si la posición cumple con la condición de distancia
            bool distanciaAceptable = true;
            for (int j = 0; j < filas; ++j) {
                if (mapa[j][2][0] == 'T' && abs(j - posicion) < 4) {
                    distanciaAceptable = false;
                    break;
                }
            }

            if (distanciaAceptable) {
                break;
            }
        } while (true);

        // Colocar la torre en la posición generada
        mapa[posicion][2][0] = 'T';
    }

    // Obtener posiciones vacías en las columnas 0 y 3
    vector<pair<int, int>> posiciones_vacias;
    for (int i = 0; i < filas; i++) {
        if (mapa[i][0][0] == ' ' && mapa[i][3][0] == ' ') {
            posiciones_vacias.push_back({i, 0});
            posiciones_vacias.push_back({i, 3});
        }
    }

    // Número de ingenieros por cada bando
    int ingenieros_1 = num_torres_bando1 / 2;  // Puedes ajustar esto según tus necesidades

    for (int i = 0; i < ingenieros_1 && !posiciones_vacias.empty(); ++i) {
        // Elegir aleatoriamente una posición vacía
        int indice = rand() % posiciones_vacias.size();
        int fila = posiciones_vacias[indice].first;

        // Colocar el ingeniero en la posición elegida
        mapa[fila][0][0] = 'I';

        // Eliminar la posición utilizada de las posiciones vacías
        posiciones_vacias.erase(posiciones_vacias.begin() + indice);
    }

    int ingenieros_2 = num_torres_bando2 / 2;  // Puedes ajustar esto según tus necesidades

    for (int i = 0; i < ingenieros_2 && !posiciones_vacias.empty(); ++i) {
        // Elegir aleatoriamente una posición vacía
        int indice = rand() % posiciones_vacias.size();
        int fila = posiciones_vacias[indice].first;

        // Colocar el ingeniero en la posición elegida
        mapa[fila][3][0] = 'I';

        // Eliminar la posición utilizada de las posiciones vacías
        posiciones_vacias.erase(posiciones_vacias.begin() + indice);
    }

    
// Número de héroes por cada bando
int heroes_1 = 1;  // Un héroe por bando
for (int i = 0; i < heroes_1 && !posiciones_vacias.empty(); ++i) {
    // Elegir aleatoriamente una posición vacía
    int indice = rand() % posiciones_vacias.size();
    int fila = posiciones_vacias[indice].first;

    // Colocar el héroe en la posición elegida
    mapa[fila][1][0] = 'H';

    // Eliminar la posición utilizada de las posiciones vacías
    posiciones_vacias.erase(posiciones_vacias.begin() + indice);
}

int heroes_2 = 1;  // Un héroe por bando
for (int i = 0; i < heroes_2 && !posiciones_vacias.empty(); ++i) {
    // Elegir aleatoriamente una posición vacía
    int indice = rand() % posiciones_vacias.size();
    int fila = posiciones_vacias[indice].first;

    // Colocar el héroe en la posición elegida
    mapa[fila][2][0] = 'H';

    // Eliminar la posición utilizada de las posiciones vacías
    posiciones_vacias.erase(posiciones_vacias.begin() + indice);
}

// Probabilidades de aparición de personajes en celdas vacías
for (int i = 0; i < filas; ++i) {
        if (mapa[i][1][0] == ' ') {
            int probabilidad = rand() % 100 + 1;  // Número aleatorio entre 1 y 100

            if (probabilidad <= 30) {
                mapa[i][1][0] = 'S';  // Soldado con probabilidad del 30%
                
            } else if (probabilidad <= 45) {
                mapa[i][1][0] = 'A';  // Arquero con probabilidad del 15%
            } else if (probabilidad <= 65) {
                mapa[i][1][0] = 'C';  // Caballero con probabilidad del 20%
            } else if (probabilidad <= 75) {
                mapa[i][1][0] = 'Z';  // Zombie con probabilidad del 10%
            } else {
                // Sin personaje con probabilidad del 25%
            }
        }
    }

for (int i = 0; i < filas; ++i) {
        if (mapa[i][2][0] == ' ') {
            int probabilidad = rand() % 100 + 1;  // Número aleatorio entre 1 y 100

            if (probabilidad <= 30) {
                mapa[i][2][0] = 'S';  // Soldado con probabilidad del 30%
            } else if (probabilidad <= 45) {
                mapa[i][2][0] = 'A';  // Arquero con probabilidad del 15%
            } else if (probabilidad <= 65) {
                mapa[i][2][0] = 'C';  // Caballero con probabilidad del 20%
            } else if (probabilidad <= 75) {
                mapa[i][2][0] = 'Z';  // Zombie con probabilidad del 10%
            } else {
                // Sin personaje con probabilidad del 25%
            }
        }
    }

int contador_no_medicos_bando1 = 0;
int contador_no_medicos_bando2 = 0;
// Generar médicos en el bando 1 (columna 0)
for (int i = 0; i < filas; ++i) {
    if (mapa[i][0][0] != 'T' && mapa[i][0][0] != 'M' && mapa[i][0][0] != ' ') {
        contador_no_medicos_bando1++;
    }
    if (mapa[i][1][0] != 'T' && mapa[i][1][0] != 'M' && mapa[i][1][0] != ' ') {
        contador_no_medicos_bando1++;
    }
}

// Generar médicos en el bando 2 (columna 3)
for (int i = 0; i < filas; ++i) {
    if (mapa[i][2][0] != 'T' && mapa[i][2][0] != 'M' && mapa[i][2][0] != ' ') {
        contador_no_medicos_bando2++;
    }
    if (mapa[i][3][0] != 'T' && mapa[i][3][0] != 'M' && mapa[i][3][0] != ' ') {
        contador_no_medicos_bando2++;
    }
}
for (int i = 0; i < contador_no_medicos_bando1/5; i++){
    int posicion = rand() % filas;
    if (mapa[posicion][0][0] != ' '){
        i--;
    }
    else{
        mapa[posicion][0][0] = 'M';
    }

}
for (int i = 0; i < contador_no_medicos_bando2/5; i++){
    int posicion = rand() % filas;
    if (mapa[posicion][3][0] != ' '){
        i--;
    }
    else{
        mapa[posicion][3][0] = 'M';
    }

}

}

void imprimir_mapa(const vector<Personaje>& personajes, int filas) {
    cout << "\toeste\teste" << endl;
    for (int i = 0; i < filas*4; i+=4) {
    if (personajes[i].codigo != " "){
    cout << personajes[i].codigo << " " << personajes[i].salud_base << "\t";}
    else {
        cout << "\t";
    }
    if (personajes[i+1].codigo != " "){
    cout << personajes[i + 1].codigo << " " << personajes[i + 1].salud_base << "\t";}
    else {
        cout << "\t";
    }
    if (personajes[i+2].codigo != " "){
    cout << personajes[i + 2].codigo << " " << personajes[i + 2].salud_base << "\t";}
    else {
        cout << "\t";
    }
    if (personajes[i+3].codigo != " "){
    cout << personajes[i + 3].codigo << " " << personajes[i + 3].salud_base << "\t";}
    else {
        cout << "\t";
    }
    cout << endl;}
    cout << "-------------------------------"<<endl;
}

void atacar(vector<Personaje>& personajes){
    for (long unsigned int i= 0 ; i < personajes.size(); i++){
        string direccion = personajes[i].direccion_ataque;
        int alcance = personajes[i].alcance_max;
        //int pos_x = personajes[i].posx;
        //int pos_y = personajes[i].posy;
        bool ataco = false;

        string team_atacante = personajes[i].team;
        if (team_atacante == "O" && personajes[i].codigo != "I" && personajes[i].codigo != "M"){
            if (direccion.find("H")!= string::npos){
                for (int j = 0; j <= alcance; j++){
                    if (personajes[i+j].team != team_atacante){
                        personajes[i].actuar(personajes[i+j]);
                        ataco = true;
                        cout << personajes[i+j].codigo <<endl;
                    }
                }
            } 
            if (direccion.find("V")!= string::npos && ataco == false){
                for (int j = -alcance; j <= alcance; j++){
                    if (personajes[i+4*j].team != team_atacante){
                        try{
                            personajes[i].actuar(personajes[i+4*j]);
                            ataco = true;}
                        catch(int a){
                            
                        }
                    }
                    
                }
            } 
            if (direccion.find("D")!= string::npos && ataco == false){
                for (int j = -alcance; j <= alcance; j++){
                    if (personajes[i + 4*j + abs(j)].team != team_atacante){
                        try{
                            personajes[i].actuar(personajes[i+4*j]);
                            ataco = true;}
                        catch(int a){
                            
                        }
                    }
                    
                }
            } 
        }
        else{

        }

    }

}


void liberar_memoria(char***& mapa, int filas) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < 4; j++) {
            free(mapa[i][j]);
        }
        free(mapa[i]);
    }
    free(mapa);
}


