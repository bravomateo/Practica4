#include "routers.h"

// Extrae la informacion de la red del archivo "red.txt" y
// lo transforma en un mapa de clave char con valor router
void iniciarRouters(map <char,routers> &ff);

//Agrega un enrutador con los parametros del usuario y
//queda guardado en map: ff
void agregarRouter(map <char,routers> &ff);

//elimina un enrutador dado por el usuario
void eliminarRouter(map <char,routers> &ff);

//Imprime la tabla de enrutamiento de la red
void mostrarRoutersRed(map <char,routers> &ff);

//agrega un enlace a el enrutador dado por el usuario
void agregarEnlaceRouter(map <char,routers> &ff);

//elimina un enlace a el enrutador dado por el usuario
void eliminarEnlaceRouter(map <char,routers> &ff);

//edita el enlace de un enrutador
void editarEnlaceRouter(map <char,routers> &ff);

//genera una red de hasta 30 nodos de forma aleatoria
void generarRedRandom(map <char,routers> &ff);

//guarda las modificaciones de la red en el archivo "red.txt"
void cerrarRouters(map <char,routers> &ff);

void buscarRutaOptima(map <char,routers> ff);
//utiliza el algoritmo de Floyd-Warshall para calcular la ruta de menor costo entre
//los enrutadores y el usuario escoge el enlace a calcular

//convierte un string a un numero tipo long int
long int str2int(string a);

//convierte un un numero tipo long int a un string
string int2str(int long a);
