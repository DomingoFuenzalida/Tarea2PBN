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
void actuar(vector<Personaje>& personajes);
bool is_in_range(int attackerPos, int targetPos, int range);
void moverse(vector<Personaje>& personajes);

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

    int co = 0;
    int ce = 0;
    bool continuar = true;
    imprimir_mapa(personajes, cantidad_filas);
    this_thread::sleep_for(chrono::milliseconds(1000));
    do{
    
    actuar(personajes);
    this_thread::sleep_for(chrono::milliseconds(1000));
    imprimir_mapa(personajes, cantidad_filas);

    co = 0;
    ce = 0;
    for (long unsigned int i=0; i < personajes.size(); i++){
        
            if (personajes[i].team == "E"){
                ce++;
            }
            else if (personajes[i].team == "O"){
                co++;
            }}
    
    if (ce == 0 || co == 0){
        continuar = false;}}
    while(continuar == true);
    imprimir_mapa(personajes, cantidad_filas);

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

    
    srand(time(0));

    int num_torres_bando1 = rand() % (filas / 5) + 1;
    int num_torres_bando2 = rand() % (filas / 5) + 1;

    for (int i = 0; i < num_torres_bando1; ++i) {
        int posicion;

        do {
           
            posicion = rand() % filas;

 
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

        
        mapa[posicion][1][0] = 'T';
    }

    for (int i = 0; i < num_torres_bando2; ++i) {
        int posicion;

        do {
            
            posicion = rand() % filas;

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

        mapa[posicion][2][0] = 'T';
    }

    vector<pair<int, int>> posiciones_vacias;
    for (int i = 0; i < filas; i++) {
        if (mapa[i][0][0] == ' ' && mapa[i][3][0] == ' ') {
            posiciones_vacias.push_back({i, 0});
            posiciones_vacias.push_back({i, 3});
        }
    }


    int ingenieros_1 = num_torres_bando1 / 2; 

    for (int i = 0; i < ingenieros_1 && !posiciones_vacias.empty(); ++i) {
        
        int indice = rand() % posiciones_vacias.size();
        int fila = posiciones_vacias[indice].first;

        
        mapa[fila][0][0] = 'I';

        
        posiciones_vacias.erase(posiciones_vacias.begin() + indice);
    }

    int ingenieros_2 = num_torres_bando2 / 2;  

    for (int i = 0; i < ingenieros_2 && !posiciones_vacias.empty(); ++i) {
        
        int indice = rand() % posiciones_vacias.size();
        int fila = posiciones_vacias[indice].first;

        
        mapa[fila][3][0] = 'I';

        
        posiciones_vacias.erase(posiciones_vacias.begin() + indice);
    }

    

int heroes_1 = 1; 
for (int i = 0; i < heroes_1 && !posiciones_vacias.empty(); ++i) {
    
    int indice = rand() % posiciones_vacias.size();
    int fila = posiciones_vacias[indice].first;

    
    mapa[fila][1][0] = 'H';

    
    posiciones_vacias.erase(posiciones_vacias.begin() + indice);
}

int heroes_2 = 1;
for (int i = 0; i < heroes_2 && !posiciones_vacias.empty(); ++i) {
 
    int indice = rand() % posiciones_vacias.size();
    int fila = posiciones_vacias[indice].first;

   
    mapa[fila][2][0] = 'H';

  
    posiciones_vacias.erase(posiciones_vacias.begin() + indice);
}


for (int i = 0; i < filas; ++i) {
        if (mapa[i][1][0] == ' ') {
            int probabilidad = rand() % 100 + 1;  

            if (probabilidad <= 30) {
                mapa[i][1][0] = 'S'; 
                
            } else if (probabilidad <= 45) {
                mapa[i][1][0] = 'A'; 
            } else if (probabilidad <= 65) {
                mapa[i][1][0] = 'C'; 
            } else if (probabilidad <= 75) {
                mapa[i][1][0] = 'Z'; 
            } else {
                
            }
        }
    }

for (int i = 0; i < filas; ++i) {
        if (mapa[i][2][0] == ' ') {
            int probabilidad = rand() % 100 + 1;  

            if (probabilidad <= 30) {
                mapa[i][2][0] = 'S';  
            } else if (probabilidad <= 45) {
                mapa[i][2][0] = 'A';  
            } else if (probabilidad <= 65) {
                mapa[i][2][0] = 'C';  
            } else if (probabilidad <= 75) {
                mapa[i][2][0] = 'Z';  
            } else {
                
            }
        }
    }

int contador_no_medicos_bando1 = 0;
int contador_no_medicos_bando2 = 0;

for (int i = 0; i < filas; ++i) {
    if (mapa[i][0][0] != 'T' && mapa[i][0][0] != 'M' && mapa[i][0][0] != ' ') {
        contador_no_medicos_bando1++;
    }
    if (mapa[i][1][0] != 'T' && mapa[i][1][0] != 'M' && mapa[i][1][0] != ' ') {
        contador_no_medicos_bando1++;
    }
}


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
    cout << personajes[i].codigo << " " << personajes[i].salud << "\t";}
    else {
        cout << "\t";
    }
    if (personajes[i+1].codigo != " "){
    cout << personajes[i + 1].codigo << " " << personajes[i + 1].salud << "\t";}
    else {
        cout << "\t";
    }
    if (personajes[i+2].codigo != " "){
    cout << personajes[i + 2].codigo << " " << personajes[i + 2].salud << "\t";}
    else {
        cout << "\t";
    }
    if (personajes[i+3].codigo != " "){
    cout << personajes[i + 3].codigo << " " << personajes[i + 3].salud << "\t";}
    else {
        cout << "\t";
    }
    cout << endl;}
    cout << "-------------------------------"<<endl;
}
bool is_in_range(int attackerPos, int targetPos, int range) {
    return abs(attackerPos - targetPos) <= range;
}
void actuar(vector<Personaje>& personajes) {
    for (vector<Personaje>::size_type i = 0; i < personajes.size(); ++i) {
            
                if (typeid(Medico) != typeid(personajes[i]) && (typeid(Ingeniero)!= typeid(personajes[i]))){
                    for (vector<Personaje>::size_type j = 0; j < personajes.size(); ++j) {
                        if (((personajes[j].posx == 2 || personajes[j].posx == 3) && personajes[j].team != " ") &&
                            is_in_range(personajes[i].posy, personajes[j].posy, personajes[i].alcance_max)) {
                            personajes[i].actuar(personajes[j]);
                        }
                    }
                }
                else if (typeid(Medico)== typeid(personajes[i])){
                    Medico& medico = dynamic_cast<Medico&>(personajes[i]);
                    for (vector<Personaje>::size_type j = 0; j < personajes.size(); ++j) {
                        if (((personajes[j].posx == 0 || personajes[j].posx == 1) && personajes[j].team != " ") &&
                            is_in_range(personajes[i].posy, personajes[j].posy, personajes[i].alcance_max)) {
                            medico.actuar(personajes[j]);
                        }
                    }
                }
                else if (typeid(Ingeniero)== typeid(personajes[i])){
                    Ingeniero& ingeniero = dynamic_cast<Ingeniero&>(personajes[i]);
                    for (vector<Personaje>::size_type j = 0; j < personajes.size(); ++j) {
                        if (((personajes[j].posx == 0 || personajes[j].posx == 1) && personajes[j].team != " ") &&
                            is_in_range(personajes[i].posy, personajes[j].posy, personajes[i].alcance_max)) {
                            ingeniero.actuar(personajes[j]);
                        }
                    }
                }
         
            if (personajes[i].posx == 2 || personajes[i].posx == 3) {
                
                if (typeid(Medico) != typeid(personajes[i]) && (typeid(Ingeniero)!= typeid(personajes[i]))){
                    for (vector<Personaje>::size_type j = 0; j < personajes.size(); ++j) {
                        if (((personajes[j].posx == 1 || personajes[j].posx == 0 )&& personajes[j].team != " ") &&
                            is_in_range(personajes[i].posy, personajes[j].posy, personajes[i].alcance_max)) {
                            personajes[i].actuar(personajes[j]);
                        }
                    }
                }
                else if (typeid(Medico)== typeid(personajes[i])){
                    Medico& medico = dynamic_cast<Medico&>(personajes[i]);
                    for (vector<Personaje>::size_type j = 0; j < personajes.size(); ++j) {
                        if (((personajes[j].posx == 2 || personajes[j].posx == 3) && personajes[j].team != " ") &&
                            is_in_range(personajes[i].posy, personajes[j].posy, personajes[i].alcance_max)) {
                            medico.actuar(personajes[j]);
                        }
                    }
                }
                else if (typeid(Ingeniero)== typeid(personajes[i])){
                Ingeniero& ingeniero = dynamic_cast<Ingeniero&>(personajes[i]);
                for (vector<Personaje>::size_type j = 0; j < personajes.size(); ++j) {
                    if (((personajes[j].posx == 2 || personajes[j].posx == 3) && personajes[j].team != " ") &&
                        is_in_range(personajes[i].posy, personajes[j].posy, personajes[i].alcance_max)) {
                        ingeniero.actuar(personajes[j]);
                    }
                }
                }
                

    }}
    this_thread::sleep_for(chrono::milliseconds(50));
    moverse(personajes);}
void moverse(vector<Personaje>& personajes){
    for (vector<Personaje>::size_type i = 0; i < personajes.size(); ++i){
        int max = personajes[i].desplazamiento;
        int mov = rand()%(max+1);
        int dir = rand()%2;
        if (dir == 1){
            mov = -mov;
        }

        long unsigned int target = i+ mov*4;
        int target2 = i+ mov*4;
        
        if (target <= 0 || target > personajes.size() || personajes[target2].codigo != " "){
            continue;
        }
        else{
            personajes[i].desplazarse(target2, personajes, i);
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


