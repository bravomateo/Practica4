#include "funciones.h"

void iniciarRouters(map <char,routers> &ff){
    char enlaces[2];
    char s;
    bool ban = false;
    string txt, co;
    long int costo;

    unsigned long long int l=1,j=0;
    routers ru;

    // leer el archivo
    // Almacenar en el string txt toda la informacion contenida en red.txt
    fstream archivo("red.txt", ios::in);
    for(long long int i=0 ; !archivo.eof() ; i++){
        archivo.get(s);
        txt.push_back(s);
    }


    txt.pop_back(); // eliminar el ultimo caracter
    archivo.close();

    for (unsigned long long int i=0; i < txt.length() ; i++) if(txt[i]=='\n') l++; // contar las lineas del archivo

    map <char,routers>::iterator rf;
    map <char,routers>::iterator rs;

    for(unsigned long long int i=0 ; i<l ; i++){

        // leer la informacion del enlace y el costo
        // Extraer informacion de la linea i, dos routers y el costo del enlace entre los dos routers

        for( ; txt[j] != '\n' && j < txt.length() ; j++){
            if((int(txt[j]) >= 65 && int(txt[j]) <= 90)||(int(txt[j]) >= 97 && int(txt[j]) <= 122)){ // Es una letra
                enlaces[ban] = txt[j];  // guardar la informacion en el arreglo en
                ban=!ban;
            }
            else if(int(txt[j]) >= 48 && int(txt[j]) <= 57) co.push_back(txt[j]); // agregar el costo al string co
        }


        j++;
        costo = str2int(co);
        co = "";
        rf = ff.find(enlaces[0]);
        rs = ff.find(enlaces[1]);

        // verificar si el router enlaces[0] existe en ff
        if(rf == ff.end()){
            ff.insert(pair<char,routers>(enlaces[0],ru));      // crear nuevo elemento en ff con la clave enlaces[0]-> nombre router y valor 'router'
            ff[enlaces[0]].crear_enlace(enlaces[0],0);         // crear un enlace hacia el mismo enlaces[0] con valor 0
            ff[enlaces[0]].crear_enlace(enlaces[1],costo);     // crear un enlcae hacia enlaces[1] con el valor 'costo'
        }
        else ff[enlaces[0]].crear_enlace(enlaces[1],costo);    // Si el router ya existe en el mapa, agregar enlace hacia enlaces[1] con el valor 'costo'

        // verificar si el router enlaces[1] existe en ff
        if(rs == ff.end()){
            ff.insert(pair<char,routers>(enlaces[1],ru));     // crear nuevo elemento en ff con la clave enlaces[1]-> nombre router y valor 'router'
            ff[enlaces[1]].crear_enlace(enlaces[1],0);        // crear un enlace hacia el mismo enlaces[1] con valor 0
            ff[enlaces[1]].crear_enlace(enlaces[0],costo);    // crear un enlace hacia enlaces[1] con valor 0
        }
        else ff[enlaces[1]].crear_enlace(enlaces[0],costo);   // Si el router ya existe en el mapaa, agregar enlace hacia enlaces[0] con el valor 'costo'
    }

}

void mostrarRoutersRed(map <char,routers> &ff){
    string list = "";
    unsigned int l = ff.size();

    map <char,long int> fs;
    map <char,routers>::iterator rf;
    map <char,int long>::iterator rs;

    for(rf = ff.begin(); rf != ff.end(); rf++) list.push_back(rf->first);
    cout<<"-----";

    for(unsigned int i=0; i<l; i++) cout << "----";
    cout << endl << '|' << "   |";

    for(rf=ff.begin();rf != ff.end(); rf++) cout<<' ' << rf->first << " |";
    cout << endl << "-----";

    for(unsigned int i=0; i<l; i++)cout<<"----";
    cout<<endl;

    for(rf = ff.begin(); rf != ff.end(); rf++){
        cout << "| " << rf->first << " |";

        fs=rf->second.cos;
        rs=fs.begin();

        for(unsigned int j=0; j<l; j++){

            if(rs->first==list[j]){
                if((rs->second)<10) cout<<' '<<rs->second<<" |";
                else if(((rs->second)/10)<10)  cout << ' ' << rs->second << "|";
                else if(((rs->second)/100)<10) cout << rs->second << "|";
                rs++;
            }
            else cout << " - |";

        }
        cout << endl << "-----";
        for(unsigned int i=0; i<l; i++) cout << "----";
        cout << endl;
    }
}

void agregarRouter(map <char,routers> &ff){

    map <char,routers>::iterator rf;
    routers router;

    char nuevo, enlace;
    bool ban;
    int costo;

    string text,temp;

    cout << endl <<"Ingrese la letra del router que desea agregar: ";
    cin >> nuevo;

    rf = ff.find(nuevo);
    if( !(rf == ff.end()) ){ // verificar que el nuevo enrutador no exista
        cout << " El router ya existe en la red!" << endl;
        return;
    }
    else{

        ff.insert(pair<char, routers>(nuevo, router));  // crear nuevo elemento en ff con la clave nuevo y valor 'router'
        ff[nuevo].crear_enlace(nuevo,0);                // crear enlace de nuevo con nuevo de costo 0

        cout << endl << "Desea agregar un enlace con " << nuevo << " (Si 1, No 0): ";
        cin >> ban;

        while(ban){ // mientras se siga agregando enlaces
            do{ cout << endl << "Hacia que router va enlazar?: ";
                cin >> enlace;
                rf = ff.find(enlace);

                // Verificar que el enrutador al que se le desea agregar enlance no exista
                if(rf == ff.end()) cout << endl << "El enrutador" << enlace << "ingresado no existe en la red";
            }while(rf == ff.end());

            cout << endl << "Ingrese costo del enlace: ";
            cin >> costo;
            ff[nuevo].crear_enlace(enlace,costo); // crear un enlace para 'nuevo' hacia 'enlace' con costo 'costo'
            ff[enlace].crear_enlace(nuevo,costo); // crear un enlace para 'enlace' hacia 'nuevo' con costo 'costo'

            cout << endl << "Desea agregar mas enlaces a " << nuevo << " (Si 1, No 0): ";
            cin >> ban;
        }

        ban = 0;
        cout << endl << "Desea ver la tabla del nuevo enrutador ingresado? (Si 1, No 0) ";
        cin >> ban;
        if (ban) ff[nuevo].ver_enrutador(nuevo);
    }
}

void eliminarRouter(map <char,routers> &ff){
    char eli;
    map <char,routers>::iterator rf;
    map <char,long int>::iterator rs;

    cout << "Ingrese el router a eliminar?: "<<endl;
    cin >> eli;

    // Veirificar la existencia del router a eliminar
    rf = ff.find(eli);
    if(rf == ff.end()) cout << "El router " << eli << " no esta en la tabla de routers\n";

    else{
        ff.erase(eli); // eliminar el enrutador del mapa ff
        // recorrer el mapa para eliminar los enlaces con el router eliminado
        for(rf = ff.begin(); rf != ff.end(); rf++){

            rs = (rf->second.cos).find(eli); // se busca la tabla de enrutamiento de router

            //Si rs no es igual a .end(), se ha encontrado al router que se desea eliminar y se debe eliminar
            if(rs != (rf->second.cos).end()) (rf->second.cos).erase(eli);
        }
    }
}

void agregarEnlaceRouter(map <char,routers> &ff){
    char cam1, cam2;
    int long costo=0;
    map <char,routers>::iterator rf;

    cout << "A que enrutador desea agregar un enlace?: ";
    cin >> cam1;

    rf = ff.find(cam1);
    // Verificar si el router cam1 existe
    if(rf == ff.end()){
        cout<<"El router " << cam1 << " no existe en la red" << endl;
        return;
    }

    cout << "Con que router lo quiere enlazar?: ";
    cin >> cam2;

    rf=ff.find(cam2);
    // Verificar si el router cam2 existe
    if(rf==ff.end()){
         cout<<"El router " << cam2 << " no existe en la red" << endl;
        return;
    }

    cout << "Costo del nuevo enlace?: ";
    cin >> costo;

    (ff[cam1].cos).insert(pair<char,int long>(cam2,costo));  // agregar un componente al objeto cam1, agrega un enlace a router 'cam2' con costo 'costo'
    (ff[cam2].cos).insert(pair<char,int long>(cam1,costo));  // agregar un componente al objeto cam2, agrega un enlace a router 'cam1' con costo 'costo'

    /*
    ff[enlaces[0]].crear_enlace(enlaces[0],0);         // crear un enlace hacia el mismo enlaces[0] con valor 0
    ff[enlaces[0]].crear_enlace(enlaces[1],costo);     // crear un enlcae hacia enlaces[1] con el valor 'costo'
    */

}

void editarEnlaceRouter(map <char,routers> &ff){
    char cam1, cam2;
    int long costo=0;
    map <char,routers>::iterator rf;

    cout << "A que enrutador desea editar el costo?: ";
    cin >> cam1;

    rf = ff.find(cam1);
    // Verificar si el router cam1 existe
    if(rf == ff.end()){
        cout<<"El router " << cam1 << " no existe en la red" << endl;
        return;
    }

    cout << "Ingrese el router con el que se desea editar el costo?: ";
    cin >> cam2;

    rf=ff.find(cam2);
    // Verificar si el router cam2 existe
    if(rf==ff.end()){
         cout<<"El router " << cam2 << " no existe en la red" << endl;
        return;
    }

    cout << "Costo del nuevo enlace?: ";
    cin >> costo;

    ff[cam1].editar_enlace(cam2,costo); // crear un enlace para 'nuevo' hacia 'enlace' con costo 'costo'
    ff[cam2].editar_enlace(cam1,costo); // crear un enlace para 'enlace' hacia 'nuevo' con costo 'costo'


}

void eliminarEnlaceRouter(map <char,routers> &ff){
    char cam1,cam2;
    map <char,routers>::iterator rf;

    cout<<"Ingrese router al que desea eliminar el enlace?: ";
    cin >> cam1;
    rf = ff.find(cam1);
    // Verificar si el router cam1 existe
    if(rf == ff.end()){
        cout << "El enrutador " << cam1 << " no existe en la red" << endl;
        return;
    }

    cout<<" Con cual enrutador desea eliminar el enlace?: ";
    cin>>cam2;
    rf=ff.find(cam2);
    // Verificar si el router cam2 existe
    if(rf==ff.end()){
        cout << "El enrutador " << cam2 << " no existe en la red" << endl;
        return;
    }

    (ff[cam1].cos).erase(cam2); // para el objeto cam1 eliminar del mapa de costos el componente con clave cam2
    (ff[cam2].cos).erase(cam1); // para el objeto cam2 eliminar del mapa de costos el componente con clave cam1
}

void cerrarRouters(map <char,routers> &ff){
    bool ban;
    string datos = "", prin = "";
    map <char,routers>::iterator rf;
    map <char,int long>::iterator rs;
    for(rf = ff.begin(); rf != ff.end(); rf++){
        for(rs=(rf->second.cos).begin(); rs!=(rf->second.cos).end(); rs++){
            ban=1;
            for(unsigned long int i=0;i<prin.length();i++) if(rs->first==prin[i]) ban=0;
            if(ban && (rf->first)!=(rs->first)){
                datos.push_back(rf->first);
                datos.push_back(' ');
                datos.push_back(rs->first);
                datos.push_back(' ');
                datos=datos + int2str(rs->second);
                datos.push_back('\n');
            }
        }
        prin.push_back(rf->first);
    }
    datos.pop_back();
    fstream archivo("red.txt", ios::out);
    archivo<<datos;
    archivo.close();
}

void generarRedRandom(map <char,routers> &ff){
    map <char,routers>::iterator rf;
    routers ru;
    int nodos,conexiones,costo;
    char nodoEnlace;
    bool ban=1;
    string datos="";
    srand(time(NULL));
    nodos=3+rand()%(9-3);
    char *red= new char[nodos];

    for(int i=0; i < nodos;){ // crear cantidad 'n = nodos' nombres para enrutadores
        ban=rand()%2; // elegir mayuscula o miniscula

        if(ban)nodoEnlace = char(65+rand()%(91-65)); // ban = true generar entre 65 y 90 (A hasta Z)
        else nodoEnlace = char(97+rand()%(123-97)); // ban = false generar entre 97 y 122 (A hasta Z)

        ban = 1;
        // Verificar que ese nombre de router no exita
        for(int j = 0;j<nodos;j++) if(red[j] == nodoEnlace) ban=0; // Si existe se pone ban = 0;

        if(ban){ // Si ban es true asigna dicho nombre al arreglo red
            red[i]=nodoEnlace;
            i++;
        }
    }
    // crear n = nodos en el mapa de redes
    for(int i=0; i<nodos; i++){
        ff.insert(pair<char,routers>(red[i],ru));
        ff[red[i]].crear_enlace(red[i],0); // crear enlace asi mismo que sea de valor 0
    }

    // crear conexiones que tendrá, incluyendo costos
    for(rf = ff.begin(); rf != ff.end(); rf++){
        conexiones = 1 + rand()%(nodos-1); // conecciones que tendra el router

        for(int i=0; i < conexiones; i++){
            nodoEnlace = red[rand()%nodos];
            costo = 1+rand()%(999);
            // crear el costo en ambas direcciones
            rf->second.crear_enlace(nodoEnlace,costo);
            ff[nodoEnlace].crear_enlace(rf->first,costo);
        }

    }
}

void buscarRutaOptima(map <char,routers> ff){
        map<char,routers>::iterator rf;
        map<char,long int>::iterator rs;
        int long long temp;

        // Matrices de enteros que representan la topología de la red.
        int long matriz_1[ff.size()][ff.size()];  // almacena los costos originales entre los routers
        int long matriz_cop[ff.size()][ff.size()]; //  copia de matriz_1 que sera modificada para calcular la ruta óptima
        char emi, rec, nodo, matriz_2[ff.size()][ff.size()];

        /*
         identificador del router de origen (emi)
         identificador del router de destino (rec)
         identificador de un nodo intermedio (nodo)
         matriz_2 es una matriz de caracteres que almacena el identificador del nodo intermedio
        */


     // inicializar  matriz_2, que se utiliza para almacenar los nodos de la red de routers.
    for(unsigned int i=0; i<ff.size(); i++){
        rf = ff.begin();
        for(unsigned int j=0; j<ff.size(); j++){
            matriz_2[i][j] = rf->first; // Para cada [i][j] se asigna el caracter al router en la posición j del mapa ff
            rf++;
        }
    } // La matriz de recorridos matriz_2

    rf = ff.begin();
    for(unsigned int i=0; i<ff.size(); i++){
        for(unsigned int j=0; j<ff.size(); j++){
            // verificar si la clave no se encontró en el mapa
            if( (rf->second.cos).find(matriz_2[i][j]) == (rf->second.cos).end() ){
                matriz_1[i][j] =-1;
                matriz_cop[i][j] =-1;}
            else{ // si la clave se encotro asignar el costo
                matriz_1[i][j] = (rf->second.cos)[matriz_2[i][j]];
                matriz_cop[i][j] = (rf->second.cos)[matriz_2[i][j]];}
        }
        rf++;
    } // La matriz distancias matriz_1 y matriz_cop

    // algoritmo de Floyd-Warshall
    for(unsigned int k=0;k<ff.size();k++){
        nodo = matriz_2[k][k];
        for(unsigned int i=0; i<ff.size(); i++){
            for(unsigned int j=0; j<ff.size(); j++){
                if(matriz_1[i][k] >= 0 && matriz_1[k][j] >= 0){
                    temp=matriz_1[i][k]+matriz_1[k][j];
                    if(temp<matriz_cop[i][j] || matriz_cop[i][j]==-1){
                        matriz_cop[i][j] = temp;
                        matriz_2[i][j] = nodo;
                    }
                }
            }
        }
    }

    map <char,unsigned int> enl;
    rf=ff.begin();
    for(unsigned int i=0;i<ff.size();i++,rf++)
        enl.insert(pair<char,unsigned int>(rf->first,i));
    cout<<"Router de origen: ";
    cin>>emi;
    cout<<"Router de destino: ";
    cin>>rec;
    if(enl.find(emi)==enl.end() || enl.find(rec)==enl.end()){
        cout<<"El router de origen o destino no existen";
        return;}
    cout<<"El camino optimo para ir de " << emi << " hasta " << rec << " es: ";
    cout << emi << "->";
    temp = enl[rec];
    while(matriz_2[temp][enl[emi]]!=rec && matriz_2[temp][enl[emi]]!=emi){
        cout<<matriz_2[temp][enl[emi]]<<"->";
        temp=enl[matriz_2[temp][enl[emi]]];
    }
    cout<<rec<<" tiene un costo de = "<<matriz_cop[(enl[emi])][(enl[rec])]<<endl;
}

long int str2int(string a){
    int b,l,d=1,c=0;
    l=a.length();
    for(int i=l-1;i>=0;i--){
        b=a[i]-48;
        c+=b*d;
        d*=10;
    }
    return c;
}

string int2str(int long a){
    int c=0,i=1;
    char e;
    string b;
    for(;(a/i);i=i*10)
        c++;
    for(int j=0;j<c;j++){
        i/=10;
        e=(a/i)+48;
        b.push_back(e);
        a-=(a/i)*i;
    }
    return b;
}
