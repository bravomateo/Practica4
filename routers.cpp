#include "routers.h"

bool routers::crear_enlace(char enlace,int long costo){
    r = cos.find(enlace);  // buscar si existe un enlance con la clave enlace
    if(r == cos.end()) cos.insert(pair<char,int long>(enlace,costo)); // si no se encuentra ningun enlace con la clave
    return r == cos.end(); // devuelve true si se insero, sino devuelve false

}

bool routers::editar_enlace(char enlace, int long costo_nuevo){
    r = cos.find(enlace);  // buscar si existe un enlace con la clave enlace
    if(r != cos.end()){ // si se encuentra el enlace
        r->second = costo_nuevo; // editar su costo
        return true;
    }
    return false; // si no se encuentra el enlace, devolver false
}


void routers::ver_enrutador(char rut){

    // Impresion de los enlaces que posee mi router
    unsigned int j=cos.size();
    cout<<"-----";

    for(unsigned int i=0 ; i<j ; i++) cout<<"----";

    cout << endl << '|' << "   |";

    for(r=cos.begin();r!=cos.end();r++) cout << ' ' << r->first << " |";

    cout << endl << "-----";

    for(unsigned int i=0;i<j;i++) cout<<"----";

    cout << endl << "| " << rut <<" |";

    for(r=cos.begin() ; r!=cos.end() ; r++){
        if((r->second)<10) cout << ' ' << r->second << " |";
        else if(((r->second)/10)<10) cout << ' ' << r->second << "|";
        else if(((r->second)/100)<10) cout << r->second << "|";
    }
    cout << endl<<"-----";
    for(unsigned int i=0 ; i<j ; i++) cout<<"----";
    cout << endl;
}
