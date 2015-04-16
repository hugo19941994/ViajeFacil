#include "Header.h"
using namespace std;

void menuNegos(owners *listaOwners){
	int opcion;

	do {
		system("CLS");
		std::cout << "********** Menu Negos **********" << endl << endl;
		std::cout << "Pulse 1 para crear nego" << endl;
		std::cout << "Pulse 2 para modificar nego" << endl;
		std::cout << "Pulse 3 para consultar lista de negos" << endl;
		std::cout << "Pulse 4 para borrar nego" << endl;
		std::cout << "Pulse 0 para volver al menu principal" << endl;
		std::cin >> opcion;

		if (opcion < 1 || opcion > 5) std::cout << "Numero no valido, tiene que ser 1, 2, 3, 4 o 5" << endl;
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
	std::cout << endl;

	std::cout << "Introduce el destino: ";
	std::cin >> sel[contNegos].destino;
	std::cout << endl;

	sel[contNegos].id = contNegos;

	do {
		cin.clear();
		cin.sync();
		cout << "Introduce el numero de plazas: ";
		cin >> sel[contNegos].numeroPlazas;
	} while (!cin.good());
	std::cout << endl;

	sel[contNegos].fecha = pedirFecha();

	std::cout << "Ya se han creado los negos que usted deseaba, muchas gracias" << endl;
	
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
			std::cout << "Nego numero " << i << endl << endl;
			std::cout << "Origen: " << sel[i].origen << endl;
			std::cout << "Destino: " << sel[i].destino << endl;
			std::cout << "Id: " << sel[i].id << endl;
			std::cout << "Numero de plazas: " << sel[i].numeroPlazas << endl;
			mostrarFecha(sel[i].fecha);
		}
	}

	int negoVacio = 0;
	do {
		cin.clear();
		cin.sync();
		cout << "Que nego deseas modificar? Introduza un numero de nego que aparezca en la lista por favor" << endl;
		cin >> i;
		if (sel[i].id == -1){
			negoVacio = 1;
			cout << "Nego vacio" << endl;
		}
	} while (!(cin.good()) || (negoVacio == 1));

	std::cout << "Introduce el origen nuevo: ";
	std::cin >> sel[i].origen;
	std::cout << endl;

	std::cout << "Introduce el destino nuevo: ";
	std::cin >> sel[i].destino;
	std::cout << endl;

	do {
		cin.clear();
		cin.sync();
		cout << "Introduce el numero de plazas nuevo: ";
		cin >> sel[i].numeroPlazas;
	} while (!cin.good());
	std::cout << endl;

	sel[i].fecha = pedirFecha();

	std::cout << "La modificacion del nego con id " << i << " ha sido satisfactorio, gracias" << endl;
	system("Pause");
}

void consultarNegos(owners *listaOwners){
	system("CLS");
	int idOwner;
	nego *sel = devolverNegos(&listaOwners[0], &idOwner);

	std::cout << "Esta es tu lista actual de negos" << endl << endl;

	for (int i = 0; i < MAXNEGOS; i++){
		if (sel[i].id != -1){
			std::cout << "Nego numero " << i << endl << endl;
			std::cout << "Origen: " << sel[i].origen << endl;
			std::cout << "Destino: " << sel[i].destino << endl;
			std::cout << "Id: " << sel[i].id << endl;
			std::cout << "Numero de plazas: " << sel[i].numeroPlazas << endl;
			mostrarFecha(sel[i].fecha);
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

	std::cout << "Negos Disponibles" << endl;
	for (int i = 0; i < MAXNEGOS; i++){
		if (sel[i].id != -1){
			std::cout << "Nego numero " << i << endl << endl;
			std::cout << "Origen: " << sel[i].origen << endl;
			std::cout << "Destino: " << sel[i].destino << endl;
			std::cout << "Id: " << sel[i].id << endl;
			std::cout << "Numero de plazas: " << sel[i].numeroPlazas << endl;
			mostrarFecha(sel[i].fecha);
		}
	}

	std::cout << "Que nego deseas borrar?" << endl;
	std::cin >> i;

	sel[i].origen = "";
	sel[i].destino = "";
	sel[i].id = -1;
	sel[i].numeroPlazas = -1;
	sel[i].fecha.dia = -1;
	sel[i].fecha.mes = -1;
	sel[i].fecha.anio = -1;

	std::cout << "Enhorabuena, su nego numero " << i << " ha sido borrado correctamente, gracias." << endl;

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
				sel[i].fecha.dia = -1;
				sel[i].fecha.mes = -1;
				sel[i].fecha.anio = -1;

				i = 1;
			}
	}
	
	listaOwners[idOwner].contNegos--;

	system("Pause");
}