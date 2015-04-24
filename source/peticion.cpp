#include "header.h"
#include "peticion.h"

Peticion::Peticion(){
	this->id_ = -1;
	this->origen_ = "";
	this->destino_ = "";
	this->fecha_ = Fecha::Fecha();
	this->plazasPedidas_ = -1;
}

Peticion::Peticion(size_t id, QString origen, QString destino, Fecha fecha, size_t plazasPedidas){
	this->id_ = id;
	this->origen_ = origen;
	this->destino_ = destino;
	this->fecha_ = fecha;
	this->plazasPedidas_ = plazasPedidas;
}

Peticion::~Peticion(){

}

void Peticion::setId(size_t id){
	this->id_ = id;
}

void Peticion::setOrigen(QString origen){
	this->origen_ = origen;
}

void Peticion::setDestino(QString destino){
	this->destino_ = destino;
}

void Peticion::setFecha(Fecha fecha){
	this->fecha_ = fecha;
}

void Peticion::setPlazasPedidas(size_t plazasPedidas){
	this->plazasPedidas_ = plazasPedidas;
}

size_t Peticion::getId(){
	return this->id_;
}

QString Peticion::getOrigen(){
	return this->origen_;
}

QString Peticion::getDestino(){
	return this->destino_;
}

Fecha Peticion::getFecha(){
	return this->fecha_;
}

size_t Peticion::getPlazasPedidas(){
	return this->plazasPedidas_;
}

//Implementacion vieja - quitar
void oficina(owners *listaOwners) {
	int opcion;

	do {
		system("CLS");
		std::cout << "********** Menu Peticiones **********" << std::endl << std::endl;
		std::cout << "Pulse 1 para crear peticion" << std::endl;
		std::cout << "Pulse 2 para modificar peticion" << std::endl;
		std::cout << "Pulse 3 para consultar lista de peticiones" << std::endl;
		std::cout << "Pulse 4 para borrar peticion" << std::endl;
		std::cout << "Pulse 5 para resolver peticiones" << std::endl;
		std::cout << "Pulse 6 para consultar log" << std::endl;
		std::cout << "Pulse 0 para volver al menu principal" << std::endl;
		std::cin >> opcion;

		if (opcion < 0 || opcion > 5) std::cout << "Numero no valido, tiene que ser 1, 2, 3, 4, 5 o 6" << std::endl;
		switch (opcion) {

		case 1:
			crearPeticiones(&listaOwners[0]);
			break;

		case 2:
			modificarPeticiones(&listaOwners[0]);
			break;

		case 3:
			mostrarPeticiones(&listaOwners[0]);
			break;

		case 4:
			borrarPeticiones(&listaOwners[0]);
			break;
		case 5:
			resolucionPeticion(&listaOwners[0]);
			break;
		case 6:
			consultarLog(&listaOwners[0]);
			break;
		}
	} while (opcion != 0);
}

void crearPeticiones(owners *listaOwners) {
	system("CLS");
	int idOwner;
	int idOficina;
	peticiones *sel = devolverPeticiones(&listaOwners[0], &idOwner, &idOficina);
	int contPeticiones = listaOwners[idOwner].oficinas[idOficina].contPeticiones++; //Post incrementamos el contador
	
	if (contPeticiones >= MAXPETICIONES)
		std::cout << "Ya se ha creado el numero maximo de peticiones." << std::endl;
	else {
		//std::cout << "Introduce el id de la peticion: ";
		//std::cin >> sel[contPeticiones].id;
		sel[contPeticiones].id = contPeticiones;

		std::cout << "Introduce el origen: ";
		std::cin >> sel[contPeticiones].origen;

		std::cout << "Introduce el id de la destino: ";
		std::cin >> sel[contPeticiones].destino;

		sel[contPeticiones].fecha.pedirFecha(); //cambiar

		std::cout << "Cuantas plazas quiere?" << std::endl;
		std::cin >> sel[contPeticiones].plazasPedidas;
	}
	system("Pause");
}

void modificarPeticiones(owners *listaOwners) {
	system("CLS");
	int idOwner;
	int idOficina;
	peticiones *sel = devolverPeticiones(&listaOwners[0], &idOwner, &idOficina);
	
	mostrarPeticiones(&listaOwners[0]);

	std::cout << "Que peticion deseas modificar? Introduza un numero de peticion que aparezca en la lista por favor" << std::endl;
	int idPeticion;
	std::cin >> idPeticion;

	std::cout << "Introduce el nuevo numero de plazas: ";
	std::cin >> sel[idPeticion].plazasPedidas;
	sel[idPeticion].fecha.pedirFecha();
	system("Pause");
}

void borrarPeticiones(owners *listaOwners) {
	system("CLS");
	int idOwner;
	int idOficina;
	peticiones *sel = devolverPeticiones(&listaOwners[0], &idOwner, &idOficina);
	
	//mostrarPeticiones(&listaOwners[0]);
	std::cout << "Esta es la lista actual de peticiones: \n";
	for (int i = 0; i < MAXPETICIONES; i++) {
		if (sel[i].id != -1){
			std::cout << "ID: " << sel[i].id;
			std::cout << "Plazas Pedidas: " << sel[i].plazasPedidas;
			sel[i].fecha.mostrarFecha(sel[i].fecha);
		}
		std::cout << std::endl;
	}

	std::cout << "Que peticion deseas borrar? Introduza un numero de peticion que aparezca en la lista por favor: ";
	int idPeticion;
	std::cin >> idPeticion;
	
	sel[idPeticion].id = -1;
	sel[idPeticion].destino = "";
	sel[idPeticion].origen = "";
	sel[idPeticion].plazasPedidas = -1;
	sel[idPeticion].fecha.setDia(-1);
	sel[idPeticion].fecha.setMes(-1);
	sel[idPeticion].fecha.setAnio(-1);
	
	for (int i = idPeticion; i < MAXPETICIONES-1; i++)
		sel[i] = sel[i+1];

	//Reordenamos el array
	for (int i = 1; i < MAXPETICIONES; i++){
		if (sel[i].id != -1)
			if (sel[i - 1].id == -1){
				sel[i - 1] = sel[i];

				sel[i - 1].id--;

				sel[idPeticion].id = -1;
				sel[idPeticion].destino = "";
				sel[idPeticion].origen = "";
				sel[idPeticion].plazasPedidas = -1;
				sel[idPeticion].fecha.setDia(-1);
				sel[idPeticion].fecha.setMes(-1);
				sel[idPeticion].fecha.setAnio(-1);

				i = 1;
			}
	}

	listaOwners[idOwner].contOficinas--;

	system("Pause");
}

void mostrarPeticiones(owners *listaOwners) {
	system("CLS");
	int idOwner;
	int idOficina;
	peticiones *sel = devolverPeticiones(&listaOwners[0], &idOwner, &idOficina);

	std::cout << "Esta es la lista actual de peticiones: \n";
	for (int i = 0; i < MAXPETICIONES; i++) {
		if (sel[i].id != -1){
			std::cout << "ID: " << sel[i].id;
			std::cout << "Plazas Pedidas: " << sel[i].plazasPedidas;
			sel[i].fecha.mostrarFecha(sel[i].fecha);
		}
		std::cout << std::endl;
	}
	system("Pause");
}

void consultarLog(owners *listaOwners){
	int idOwner;
	oficinas *sel = devolverOficinas(&listaOwners[0], &idOwner);
	//TODO DECREMENTAR CONTADOR??

	//consultarOficinas(&listaOwners[0]);
	for (int i = 0; i < MAXOFICINAS; i++) {
		if (sel[i].id != -1){
			std::cout << "ID de la oficina: " << sel[i].id << std::endl;
			std::cout << "Nombre de la oficina: " << sel[i].nombre << std::endl;
			std::cout << "Pais: " << sel[i].pais << std::endl;
			std::cout << "Continente: " << sel[i].continente << std::endl << std::endl;
		}
	}

	std::cout << "Seleccione Oficina" << std::endl;
	int idOficina;
	std::cin >> idOficina;

	for (int i = 0; i < 1024; i++){
		if (listaOwners[idOwner].oficinas[idOficina].historial[i] != -1)
			std::cout << mirar(listaOwners[idOwner].oficinas[idOficina].historial[i]) << std::endl;
	}
	system("Pause");
} 

std::string mirar(int i){
	if (i == 0)
		return "Peticion Denegada";
	else
		return "Peticion Aceptada";
}

bool resolucionPeticion(owners *listaOwners){
	system("CLS");
	int idOwner;
	int idOficina;
	peticiones *sel = devolverPeticiones(&listaOwners[0], &idOwner, &idOficina);

	//mostrarPeticiones(&listaOwners[0]);
	std::cout << "Esta es la lista actual de peticiones: \n";
	for (int i = 0; i < MAXPETICIONES; i++) {
		if (sel[i].id != -1){
			std::cout << "ID: " << sel[i].id;
			std::cout << "Plazas Pedidas: " << sel[i].plazasPedidas;
			sel[i].fecha.mostrarFecha(sel[i].fecha);
		}
		std::cout << std::endl;
	}

	std::cout << "Que peticion deseas comprobar: ";
	int idPeticion;
	std::cin >> idPeticion;

	bool resultado = false;
	bool insuficientesPlazas = false;

	for (int i = 0; i < MAXNEGOS; i++){
		if ((sel[idPeticion].fecha.getAnio() == listaOwners[idOwner].negos[i].fecha.getAnio())
			&& (sel[idPeticion].fecha.getMes() == listaOwners[idOwner].negos[i].fecha.getMes())
			&& (sel[idPeticion].fecha.getDia() == listaOwners[idOwner].negos[i].fecha.getDia())
			&& (sel[idPeticion].origen == listaOwners[idOwner].negos[i].origen)
			&& (sel[idPeticion].destino == listaOwners[idOwner].negos[i].destino)){
			//posicionNego = i;
			std::cout << "El nego con ID " << listaOwners[idOwner].negos[i].id << " coincide con la peticion" << std::endl << "Comprobando plazas" << std::endl;
			if (sel[idPeticion].plazasPedidas <= listaOwners[idOwner].negos[i].numeroPlazas){
				listaOwners[idOwner].negos[i].numeroPlazas -= sel[idPeticion].plazasPedidas;
				std::cout << "Peticion aceptada" << std::endl;
				resultado = true;

				//Lo metemos en el historial
				//listaOwners[idOficina].oficinas[idOficina].historial[listaOwners[idOficina].oficinas[idOficina].contHistorial] = "Peticion Aceptada";
				listaOwners[idOwner].oficinas[idOficina].historial[listaOwners[idOwner].oficinas[idOficina].contHistorial]=1;
				listaOwners[idOficina].oficinas[idOficina].contHistorial++;

				break;
			}
			else{
				std::cout << "No hay suficientes plazas disponible en este nego" << std::endl << "El numero de plazas disponible es "
					<< listaOwners[idOwner].negos[i].numeroPlazas << std::endl << "Puede modificar su peticion si quiere";
				resultado = false;
			}
		}
	}

	if (resultado == false){
		std::cout << "No se ha encontrado ningun nego que coincida con su peticion" << std::endl;
		//listaOwners[idOficina].oficinas[idOficina].historial[listaOwners[idOficina].oficinas[idOficina].contHistorial] = "Peticion Denegada";
		listaOwners[idOwner].oficinas[idOficina].historial[listaOwners[idOwner].oficinas[idOficina].contHistorial] = 0;
		listaOwners[idOficina].oficinas[idOficina].contHistorial++;
	}
	
	system("Pause");
	
	return resultado;
}