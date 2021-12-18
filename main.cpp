#include <iostream>
using namespace std;

struct Registro {
	bool Asientos[19];
	int pasAsc;
	int pasDesc;
	int contPasajeros;
	int contParadas;
};

// Prototipos de funcion
void CargaDeDatos(Registro &data, int &contPasajeros, int asDis[], int &len);
void iniVec(int vec[], int valor, int cantPos);
void iniVecB(bool vec[], bool valor, int cantPos);
void Disponibles(bool vecEntr[], int vecSal[], int longitud, int &len);
void insertarOrdenado(int vec[], int valor, int &len);
void MostrarPorPantalla(Registro data, int asientosDis[], int len, int contParadas);
void GuardarArchivo(Registro data);

int main(){
Registro datosViaje;
bool estadoViaje;
datosViaje.contPasajeros = 0;
datosViaje.contParadas = 0;
int asDis[19]; //vector para pasar a mostrar por pantalla
int len = 0; //len del vector

iniVec(asDis, 0, 19);
iniVecB(datosViaje.Asientos, 0, 19); //inicializacion del vector de booleanos

cout << "Ingrese estado del viaje" << endl;
cin >> estadoViaje;

while (estadoViaje != 0){
	CargaDeDatos(datosViaje, datosViaje.contPasajeros, asDis, len);
    datosViaje.contParadas++;
    MostrarPorPantalla(datosViaje, asDis, len, datosViaje.contParadas);
	cout << "Ingrese estado del viaje" << endl;
	cin >> estadoViaje;
	} // fin del while

    GuardarArchivo(datosViaje);
    cout << "Pasajeros totales: " << datosViaje.contPasajeros << endl;
    cout << "Total de paradas: " << datosViaje.contParadas << endl;
    cout << "Finalizo el viaje" << endl;
    return 0;
}

void CargaDeDatos(Registro &data, int &contPasajeros, int asDis[], int &len){
    Disponibles(data.Asientos, asDis, 19, len);
    cout << "Ingrese la cantidad de pasajeros ascendidos" << endl;
    cin >> data.pasAsc;
    data.contPasajeros += data.pasAsc;
    cout << "Ingrese la cantidad de pasajeros descendidos" << endl;
    cin >> data.pasDesc;
}

void Disponibles(bool vecEntr[], int vecSal[], int longitud, int &len){
    int aux;
    int i = 0;
    cout << "Indique que asientos estan disponibles, ingrese 0 para terminar" << endl;
    cin >> aux;
    while (aux!=0 && i<longitud){
        vecEntr[aux-1] = 1; // vecEntr guarda en el vector los asientos disponibles
        insertarOrdenado(vecSal, aux, len);
        cout << "Indique que asientos estan disponibles, ingrese 0 para terminar" << endl;
        cin >> aux;
        i++;
    }
}

void MostrarPorPantalla(Registro data, int asientosDis[], int len, int contParadas){
    cout << "Los asientos libres en este momento son: ";
    for (int i = 0; i < len; i++)
        cout << asientosDis[i] << " ";
    cout << endl << "Parada N: " << contParadas << endl;
    cout << "Ascendieron: " << data.pasAsc << " pasajeros" << endl;
    cout << "Descendieron: " << data.pasDesc << " pasajeros" << endl;
}

void GuardarArchivo(Registro data){
    FILE * punt;
    punt = fopen ("Datos.dat","wb");

    Registro p;
    p.contParadas = data.contParadas;
    p.contPasajeros = data.contPasajeros;
 	fwrite(&p,sizeof(Registro),1,punt);

	fclose(punt);
}

void insertarOrdenado(int vec[], int valor, int &len){
    int pos = 0;
    while (valor > vec[pos] && pos < len)
        pos++;
    for (int i = len; pos<i; i--){
        vec[i] = vec[i-1];
    }
    vec[pos] = valor;
    len++;
}

void iniVec(int vec[], int valor, int cantPos){
    for (int i=0; i<cantPos; i++){
        vec[i] = valor;
    }
}

void iniVecB(bool vec[], bool valor, int cantPos){
    for (int i=0; i<cantPos; i++){
        vec[i] = valor;
    }
}
