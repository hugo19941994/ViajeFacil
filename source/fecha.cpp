#include <iostream>
#include "./fecha.hpp"

/* CONSTRUCTOR FECHA SIN PARÁMETROS */
Fecha::Fecha() {
    this->dia_ = 1;
    this->mes_ = 1;
    this->anio_ = 1;
}

/* CONSTRUCTOR FECHA CON PARÁMETROS */
Fecha::Fecha(size_t dia, size_t mes, int anio) {
  this->dia_ = dia;
  this->mes_ = mes;
  this->anio_ = anio;
}

/* DESTRUCTOR (al destruirse el objeto) */
Fecha::~Fecha() {
  // delete this;
}

/* MÉTODOS SET Y GET */
void Fecha::setFecha(size_t dia, size_t mes, int anio) {
  this->dia_ = dia;
  this->mes_ = mes;
  this->anio_ = anio;
}

void Fecha::setDia(size_t dia) {
  this->dia_ = dia;
}

void Fecha::setMes(size_t mes) {
  this->mes_ = mes;
}
void Fecha::setAnio(int anio) {
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
