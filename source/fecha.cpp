#include <iostream>
#include "./fecha.hpp"

Fecha::Fecha() : dia_{0}, mes_{0}, anio_{0} {}

Fecha::Fecha(size_t dia, size_t mes, int anio)
    : dia_{dia}, mes_{mes}, anio_{anio} {}

Fecha::~Fecha() {}

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
