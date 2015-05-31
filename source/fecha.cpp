/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author Fernando Saavedra
 */

#include "./fecha.hpp"

Fecha::Fecha() : dia_(0), mes_(0), anio_(0) {}

Fecha::Fecha(int dia, int mes, int anio)
    : dia_(dia), mes_(mes), anio_(anio) {}

Fecha::~Fecha() {}

void Fecha::setFecha(int dia, int mes, int anio) {
  dia_ = dia;
  mes_ = mes;
  anio_ = anio;
}

void Fecha::setDia(int dia) { dia_ = dia; }
void Fecha::setMes(int mes) { mes_ = mes; }
void Fecha::setAnio(int anio) { anio_ = anio; }

int Fecha::getDia() { return dia_; }
int Fecha::getMes() { return mes_; }
int Fecha::getAnio() { return anio_; }
