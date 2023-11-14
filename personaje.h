using namespace std;

class personaje {
public:
    char codigo;
    string tipo;
    int salud_base;
    int fuerza_max;
    int alcance_max;
    string direccion_ataque;
    int desplazamiento_max;
    int curacion;
    personaje(char codigo,string tipo, int salud_base ,int fuerza_max, int alcance_max, string direccion_ataque, int desplazamiento_max, int curacion);
    ~personaje();
    void desplazarse(int objetivo);
    void actuar(char objetivo, char accion);
};


