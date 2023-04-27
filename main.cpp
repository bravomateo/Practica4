#include "funciones.h"

int main(){

    map <char,routers> ff;
    map <char,routers>::iterator rf;
    unsigned short opcionAccion=1,opcionRouter;
    char a;

    cout << "+---------------------------------------------------+" << endl;
    cout << "|       ** Simulacion de una red de routers **      |" << endl;
    cout << "|---------------------------------------------------|" << endl;
    cout << "| 1. La red guardada en el archivo red.txt          |" << endl;
    cout << "| *las modificaciones que la red son permanentes*   |" << endl;
    cout << "+---------------------------------------------------+" << endl;
    cout << "| 2. Una red aleatoria                              |" << endl;
    cout << "+---------------------------------------------------+" << endl;
    cout << "Eliga una opcion: ";
    cin  >> opcionRouter;

    if(opcionRouter == 1) iniciarRouters(ff);  // Crear la red con routers y enlaces establecidos en red.txt
    else generarRedRandom(ff);

    while (opcionAccion != 0){

        cout << endl;
        cout << "Lista de acciones" << endl;
        cout << "1) Ver la tabla de toda la red" << endl;
        cout << "2) Ver la tabla de un enrutador" << endl;
        cout << "3) Agregar un enrutador" << endl;
        cout << "4) Eliminar un enrutador" << endl;
        cout << "5) Agregar un enlace a un enrutador ya existente" << endl;
        cout << "6) Eliminar enlace de dos enrutadores" << endl;
        cout << "7) Editar el costo del enlace de router " << endl;
        cout << "8) Costo y camino de envio de paquetes " << endl;
        cout << "0) Para salir" << endl;
        cout << "Ingrese el numero de la accion que desea realizar: ";
        cin >> opcionAccion;
        cout << endl;
        switch (opcionAccion) {
        case 1 :
            mostrarRoutersRed(ff);
            break;
        case 2 :
            cout << "Visualizar la tabla del enrutador" << endl;
            cout << "De que enrutador desea ver la tabla?: ";
            cin >> a;
            rf = ff.find(a);
            if (!(rf==ff.end())) rf->second.ver_enrutador(a);
            else cout << "*El enrutador ingresado no esta en la red!" << endl;
            break;
        case 3 :
            agregarRouter(ff);
            break;
        case 4 :
            eliminarRouter(ff);
            break;
        case 5 :
            agregarEnlaceRouter(ff);
            break;
        case 6 :
            eliminarEnlaceRouter(ff);
            break;
        case 7 :
            editarEnlaceRouter(ff);
            break;
        case 8 :
            buscarRutaOptima(ff);
            break;
        default:
            break;
        }
        if(opcionAccion!=0) system("pause");
    }
    if(opcionRouter==1) cerrarRouters(ff);
}



