#include <iostream>
#include "fecha.h"

/* CONSTRUCTOR FECHA SIN PARÁMETROS */
Fecha::Fecha()
{
    this->dia=1;
    this->mes=1;
    this->anio=1;
}
/* CONSTRUCTOR FECHA CON PARÁMETROS */
Fecha::Fecha(size_t pDia,size_t pMes,int pAnio){
  this->dia=pDia;
  this->mes=pMes;
  this->anio=pAnio;
}
/* DESTRUCTOR (al destruirse el objeto) */
Fecha::~Fecha(){
	delete this;
}
/* MÉTODOS SET Y GET */
void Fecha::setFecha(size_t pDia,size_t pMes,int pAnio){
  this->dia = pDia;
  this->mes = pMes;
  this->anio = pAnio;
}

void Fecha::setDia(size_t pDia){
  this->dia = pDia;
};
void Fecha::setMes(size_t pMes){
  this->mes = pMes;
}
void Fecha::setAnio(int pAnio){
  this->dia = pAnio;
}
size_t Fecha::getDia() {
  return this->dia;
}
size_t Fecha::getMes() {
  return this->mes;
}
int Fecha::getAnio() {
  return this->anio;
}

//quitar
Fecha Fecha::pedirFecha() {

	do {
		std::cin.clear();
		std::cin.sync();
		std::cout << "Introduce el dia:  ";
		std::cin >> this->dia;
	} while (!std::cin.good());

	do {
		std::cin.clear();
		std::cin.sync();
		std::cout << "Introduce el mes:  ";
		std::cin >> this->mes;
	} while (!std::cin.good());

	do {
		std::cin.clear();
		std::cin.sync();
		std::cout << "Introduce el anio:  ";
		std::cin >> this->anio;
	} while (!std::cin.good());

	return *this;
}

void Fecha::mostrarFecha(Fecha fecha){
	std::cout << "Fecha: ";
	std::cout << "Dia " << fecha.dia << " ";
	std::cout << "Mes " << fecha.mes << " ";
	std::cout << "Anio " << fecha.anio << std::endl;
}