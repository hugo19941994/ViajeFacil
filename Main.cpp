/*	
Proyecto:	Unisys 2015
Titulo:		Viaje Facil
Miembros:	David Jimenez Cuevas
			Hugo Ferrando Seage
			Guillermo
			Fernando Saavedra
TODO Web: https://github.com/???
Descripcion:
	Owners:		Compañias de vuelo (Iberia, Halcon Viajes)
	Negos:		Paquetes de vuelo
	Oficinas:	Sucursales de Owners
	Peticiones:	Viajes que piden las oficinas
TODO:
	Hay que hacer que cuando se aproxime a la fecha del vuelo, se le quite un 20% de peticiones a las oficinas
	En las funciones de borrar oficinas y negos, borras el contenido pero dejas el hueco en el array
	Al entrar eb oficinas no se que tengo que hacer??
	El log de peticiones ??
Log David:
	En general he añadido espacios entre variables y operadores a = 1 en vez de a=1 y lo mismo con cout<< y cin
	En las funciones de modificar y borrar nego, he cambiado la parte de mostrar los negos por la funcion que ya tenías, consultar negos
	En las funciones de modificar y borrar oficinas, lo mismo que en la anterior
	He creado una funcion para pedir la fecha, en lugar de repetir en crearNego y modificarNego el mismo código
	He creado otra función para mostrar un tFecha, en lugar de poner en todas las funciones dia, mes y anyo
	He creado una funcion que inicializa todos los campos en las listas, aunque como solo vas a utilizar la id para las comparaciones bastaria con inicializar ese campo
	Para las peticiones utilizo una lista con contador, es el array normal de peticiones y un contador que se incrementa cada vez que introduces un nuevo dato
	Añadida funcion mostrarPeticiones
*/

#include "Header.h"
using namespace std;
//MODIFICAAAAAAR

int main() {

	int opcion;
	owners listaOwners[MAXOWNERS];

	listaOwners[0].id = 0;
	listaOwners[0].nombre = "El Corte Ingles";

	listaOwners[1].id = 1;
	listaOwners[1].nombre = "Halcon Viajes";

	do {
		system("CLS");
		std::cout << "********** BIENVENIDO A LA AGENCIA MAS ORGANIZADA DEL MUNDO **********" << std::endl << std::endl << std::endl;
		std::cout << "********** Menu Principal **********" << std::endl << std::endl;
		std::cout << "Pulse 1 para acceder a Negos" << std::endl;
		std::cout << "Pulse 2 para acceder a Oficinas" << std::endl;
		std::cout << "Pulse 3 para acceder a Peticiones" << std::endl;
		std::cout << "Pulse 0 para salir" << std::endl << std::endl;
		std::cin >> opcion;
		std::cout << std::endl;

		switch (opcion) {
			case 1:
				std::cout << "Estas dentro de Compania" << std::endl << std::endl;
				menuNegos(&listaOwners[0]);
				std::cout << std::endl << std::endl;
				break;
			case 2:  std::cout << "Estas dentro de Owners" << std::endl;
				gestionarOficinas(&listaOwners[0]);
				break;
			case 3:  std::cout << "Estas dentro de Oficina" << endl;
				oficina(&listaOwners[0]);
				break;
		}
	} while (opcion != 0);

	std::cout << "Ha sido un placer, que tenga un buen dia!" << endl;

	system("Pause");

	return 0;
}

nego* devolverNegos(owners *listaOwners, int* idOwner){
	/*	Pregunta por el Owner y devuelve un puntero a sus negos
		idOwner es un puntero por si hay que acceder desde fuera al owner	*/
	std::cout << "Seleccione Owner" << endl;
	int posicion = 0;
	for (int i = 0; i < MAXOWNERS; i++){
		if (listaOwners[i].id != -1)
			std::cout << listaOwners[i].id << " " << listaOwners[i].nombre << endl;
	}
	cin >> *idOwner;
	nego *sel = &listaOwners[*idOwner].negos[0];
	return sel;
}

oficinas* devolverOficinas(owners *listaOwners, int* idOwner){
	/*	Pregunta por el Owner y devuelve un puntero a sus oficinas
		idOwner es un puntero por si hay que acceder desde fuera al owner	*/
	std::cout << "Seleccione Owner" << endl;
	int posicion = 0;
	for (int i = 0; i < MAXOWNERS; i++){
		if (listaOwners[i].id != -1)
			std::cout << listaOwners[i].id << " " << listaOwners[i].nombre << endl;
	}
	cin >> *idOwner;
	oficinas *sel = &listaOwners[*idOwner].oficinas[0];
	return sel;
}

peticiones* devolverPeticiones(owners *listaOwners, int* idOwner, int *idOficina){
	/*	Pregunta por el Owner, Oficina y devuelve un puntero a sus peticiones
		idOwner es un puntero por si hay que acceder desde fuera al owner
		idOficina es un puntero por si hay que acceder a las oficinas	*/
	std::cout << "Seleccione Owner" << endl;
	for (int i = 0; i < MAXOWNERS; i++){
		if (listaOwners[i].id != -1)
			std::cout << listaOwners[i].id << " " << listaOwners[i].nombre << endl;
	}
	cin >> *idOwner;
	oficinas *sel = &listaOwners[*idOwner].oficinas[0];

	std::cout << "Seleccione Oficina" << endl;
	int posicion = 0;
	for (int i = 0; i < MAXOFICINAS; i++){
		if (sel[i].id!= -1)
			std::cout << sel[i].id << " " << sel[i].nombre << endl;
	}
	cin >> *idOficina;
	peticiones *sel2 = &sel[*idOficina].peticiones[0];

	return sel2;
}

fecha pedirFecha() {
	fecha fecha;

	do {
		cin.clear();
		cin.sync();
		cout << "Introduce el dia:  ";
		cin >> fecha.dia;
	} while (!cin.good());

	do {
		cin.clear();
		cin.sync();
		cout << "Introduce el mes:  ";
		cin >> fecha.mes;
	} while (!cin.good());

	do {
		cin.clear();
		cin.sync();
		cout << "Introduce el anio:  ";
		cin >> fecha.anio;
	} while (!cin.good());

	return fecha;
}

void mostrarFecha(fecha fecha){
	std::cout << "Fecha: ";
	std::cout << "Dia " << fecha.dia << " ";
	std::cout << "Mes " << fecha.mes << " ";
	std::cout << "Anio " << fecha.anio << endl;
}
