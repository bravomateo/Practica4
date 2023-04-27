#include <iostream>

using namespace std;

#include <map>
#include <list>
#include <fstream>
#include <stdlib.h>
#include <time.h>

class routers
{
public:
    map <char,int long> cos;
    bool crear_enlace(char enlace, int long costo);
    bool editar_enlace(char enlace, int long costo_nuevo);
    void ver_enrutador(char rut);
private:
    map <char, int long>::iterator r;
};
