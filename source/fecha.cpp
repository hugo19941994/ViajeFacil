#include <iostream>
#include "fecha.h"

/* CONSTRUCTOR FECHA SIN PARÁMETROS */
Fecha::Fecha()
{
    this->dia_=1;
    this->mes_=1;
    this->anio_=1;
}

/* CONSTRUCTOR FECHA CON PARÁMETROS */
Fecha::Fecha(size_t dia,size_t mes,int anio){
  this->dia_=dia;
  this->mes_=mes;
  this->anio_=anio;
}

/* DESTRUCTOR (al destruirse el objeto) */
Fecha::~Fecha(){
	//delete this;
}

/* MÉTODOS SET Y GET */
void Fecha::setFecha(size_t dia,size_t mes,int anio){
  this->dia_ = dia;
  this->mes_ = mes;
  this->anio_ = anio;
}

void Fecha::setDia(size_t dia){
  this->dia_ = dia;
};
void Fecha::setMes(size_t mes){
  this->mes_ = mes;
}
void Fecha::setAnio(int anio){
  this->dia_ = anio;
}
size_t Fecha::getDia() {
  return this->dia_;
}
size_t Fecha::getMes() {
  return this->mes_;
}
int Fecha::getAnio() {
  return this->anio_;
}

//Quitar
Fecha Fecha::pedirFecha() {

	do {
		std::cin.clear();
		std::cin.sync();
		std::cout << "Introduce el dia:  ";
		std::cin >> this->dia_;
	} while (!std::cin.good());

	do {
		std::cin.clear();
		std::cin.sync();
		std::cout << "Introduce el mes:  ";
		std::cin >> this->mes_;
	} while (!std::cin.good());

	do {
		std::cin.clear();
		std::cin.sync();
		std::cout << "Introduce el anio:  ";
		std::cin >> this->anio_;
	} while (!std::cin.good());

	return *this;
}

void Fecha::mostrarFecha(Fecha fecha){
	std::cout << "Fecha: ";
	std::cout << "Dia " << fecha.dia_ << " ";
	std::cout << "Mes " << fecha.mes_ << " ";
	std::cout << "Anio " << fecha.anio_ << std::endl;
}
