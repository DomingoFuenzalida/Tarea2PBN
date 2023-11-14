using namespace std;

class personaje{
    public:
    char codigo;
    int salud_base;
    int equipo;
    int pos_x;
    int pos_y;

    void dezplazarse(int objetivo);
    void actuar(char objetivo, char accion);
};
