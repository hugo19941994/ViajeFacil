#include "header.h"
#include "nego.h"

Nego::Nego() {
	this->origen = "";
	this->destino = "";
	this->id = -1;
	this->numeroPlazas = 0;
	this->fecha = Fecha(-1, -1, -1);
}

Nego::Nego(QString origen, QString destino, int id, int numeroPlazas, Fecha fecha) {
	this->origen = origen;
	this->destino = destino;
	this->id = id;
	this->numeroPlazas = numeroPlazas;
	this->fecha = fecha;
}

Nego::~Nego() {
	//delete this;
}

void Nego::setNego(QString origen, QString destino, int id, int numeroPlazas, Fecha fecha) {
	this->origen = origen;
	this->destino = destino;
	this->id = id;
	this->numeroPlazas = numeroPlazas;
	this->fecha = fecha;
}

void Nego::setOrigen(QString origen){
	this->origen = origen;
}

void Nego::setDestino(QString destino){
	this->destino = destino;
}

void Nego::setId(int id){
	this->id = id;
}

void Nego::setNumeroPlazas(int numeroPlazas){
	this->numeroPlazas = numeroPlazas;
}

void Nego::setFecha(Fecha fecha){
	this->fecha = fecha;
}

QString Nego::getOrigen(){
	return this->origen;
}

QString Nego::getDestino(){
	return this->destino;
}

int Nego::getId(){
	return this->id;
}

int Nego::getNumeroPlazas(){
	return this->numeroPlazas;
}

Fecha Nego::getFecha(){
	return this->fecha;
}

//Negos viejo - eliminar
void menuNegos(owners *listaOwners){
	int opcion;

	do {
		system("CLS");
		std::cout << "********** Menu Negos **********" << std::endl << std::endl;
		std::cout << "Pulse 1 para crear nego" << std::endl;
		std::cout << "Pulse 2 para modificar nego" << std::endl;
		std::cout << "Pulse 3 para consultar lista de negos" << std::endl;
		std::cout << "Pulse 4 para borrar nego" << std::endl;
		std::cout << "Pulse 0 para volver al menu principal" << std::endl;
		std::cin >> opcion;

		if (opcion < 1 || opcion > 5) std::cout << "Numero no valido, tiene que ser 1, 2, 3, 4 o 5" << std::endl;
		switch (opcion) {
		case 1:
			crearNego(&listaOwners[0]);
			break;
		case 2:
			modificarNego(&listaOwners[0]);
			break;
		case 3:
			consultarNegos(&listaOwners[0]);
			break;
		case 4:
			borrarNego(&listaOwners[0]);
			break;
		}
	} while (opcion != 0);

}

void crearNego(owners *listaOwners) {
	system("CLS");

	int idOwner;
	nego *sel = devolverNegos(&listaOwners[0], &idOwner);
	int contNegos = listaOwners[idOwner].contNegos++; //Post incrementamos el contador

	std::cout << "Introduce el origen: ";
	std::cin >> sel[contNegos].origen;
	std::cout << std::endl;

	std::cout << "Introduce el destino: ";
	std::cin >> sel[contNegos].destino;
	std::cout << std::endl;

	sel[contNegos].id = contNegos;

	do {
		std::cin.clear();
		std::cin.sync();
		std::cout << "Introduce el numero de plazas: ";
		std::cin >> sel[contNegos].numeroPlazas;
	} while (!std::cin.good());
	std::cout << std::endl;

	sel[contNegos].fecha.pedirFecha();

	std::cout << "Ya se han creado los negos que usted deseaba, muchas gracias" << std::endl;
	
	system("Pause");
}

void modificarNego(owners *listaOwners){
	system("CLS");
	int i; // Posicion del array
	int opcion;

	system("CLS");

	int idOwner;
	nego *sel = devolverNegos(&listaOwners[0], &idOwner);

	//Si uso consultarNegos(&listaOwners[0]); pide el Owner dos veces...
	for (int i = 0; i < MAXNEGOS; i++){
		if (sel[i].id != -1){
			std::cout << "Nego numero " << i << std::endl << std::endl;
			std::cout << "Origen: " << sel[i].origen << std::endl;
			std::cout << "Destino: " << sel[i].destino << std::endl;
			std::cout << "Id: " << sel[i].id << std::endl;
			std::cout << "Numero de plazas: " << sel[i].numeroPlazas << std::endl;
			sel[i].fecha.mostrarFecha(sel[i].fecha); //cambiar
		}
	}

	int negoVacio = 0;
	do {
		std::cin.clear();
		std::cin.sync();
		std::cout << "Que nego deseas modificar? Introduza un numero de nego que aparezca en la lista por favor" << std::endl;
		std::cin >> i;
		if (sel[i].id == -1){
			negoVacio = 1;
			std::cout << "Nego vacio" << std::endl;
		}
	} while (!(std::cin.good()) || (negoVacio == 1));

	std::cout << "Introduce el origen nuevo: ";
	std::cin >> sel[i].origen;
	std::cout << std::endl;

	std::cout << "Introduce el destino nuevo: ";
	std::cin >> sel[i].destino;
	std::cout << std::endl;

	do {
		std::cin.clear();
		std::cin.sync();
		std::cout << "Introduce el numero de plazas nuevo: ";
		std::cin >> sel[i].numeroPlazas;
	} while (!std::cin.good());
	std::cout << std::endl;

	sel[i].fecha.pedirFecha();

	std::cout << "La modificacion del nego con id " << i << " ha sido satisfactorio, gracias" << std::endl;
	system("Pause");
}

void consultarNegos(owners *listaOwners){
	system("CLS");
	int idOwner;
	nego *sel = devolverNegos(&listaOwners[0], &idOwner);

	std::cout << "Esta es tu lista actual de negos" << std::endl << std::endl;

	for (int i = 0; i < MAXNEGOS; i++){
		if (sel[i].id != -1){
			std::cout << "Nego numero " << i << std::endl << std::endl;
			std::cout << "Origen: " << sel[i].origen << std::endl;
			std::cout << "Destino: " << sel[i].destino << std::endl;
			std::cout << "Id: " << sel[i].id << std::endl;
			std::cout << "Numero de plazas: " << sel[i].numeroPlazas << std::endl;
			sel[i].fecha.mostrarFecha(sel[i].fecha); //cambiar
		}
	}
	system("Pause");
}

void borrarNego(owners *listaOwners){
	system("CLS");
	int i;
	int opcion;

	int idOwner;
	nego *sel = devolverNegos(&listaOwners[0], &idOwner);

	std::cout << "Negos Disponibles" << std::endl;
	for (int i = 0; i < MAXNEGOS; i++){
		if (sel[i].id != -1){
			std::cout << "Nego numero " << i << std::endl << std::endl;
			std::cout << "Origen: " << sel[i].origen << std::endl;
			std::cout << "Destino: " << sel[i].destino << std::endl;
			std::cout << "Id: " << sel[i].id << std::endl;
			std::cout << "Numero de plazas: " << sel[i].numeroPlazas << std::endl;
			sel[i].fecha.mostrarFecha(sel[i].fecha);
		}
	}

	std::cout << "Que nego deseas borrar?" << std::endl;
	std::cin >> i;

	sel[i].origen = "";
	sel[i].destino = "";
	sel[i].id = -1;
	sel[i].numeroPlazas = -1;
	sel[i].fecha.setDia(-1);
	sel[i].fecha.setMes(-1);
	sel[i].fecha.setAnio(-1);

	std::cout << "Enhorabuena, su nego numero " << i << " ha sido borrado correctamente, gracias." << std::endl;

	//Reordenamos el array
	for (int i = 1; i < MAXNEGOS; i++){
		if(sel[i].id != -1)
			if (sel[i - 1].id == -1){
				sel[i - 1] = sel[i];

				sel[i - 1].id--;
				
				sel[i].origen = "";
				sel[i].destino = "";
				sel[i].id = -1;
				sel[i].numeroPlazas = -1;
				sel[i].fecha.setDia(-1);
				sel[i].fecha.setMes(-1);
				sel[i].fecha.setAnio(-1);

				i = 1;
			}
	}
	
	listaOwners[idOwner].contNegos--;

	system("Pause");
}