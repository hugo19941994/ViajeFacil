#include "./nego.hpp"
#include <string>

Nego::Nego()
    : origen_{""}, destino_{""}, numeroPlazas_{0}, fecha_{Fecha(0, 0, 0)} {}

Nego::Nego(std::string origen, std::string destino,
    int numeroPlazas, Fecha fecha)
    : origen_{origen}, destino_{destino},
    numeroPlazas_{numeroPlazas}, fecha_{fecha} {}

Nego::~Nego() {}

void Nego::setNego(std::string origen, std::string destino,
    int numeroPlazas, Fecha fecha) {
  this->origen_ = origen;
  this->destino_ = destino;
  this->numeroPlazas_ = numeroPlazas;
  this->fecha_ = fecha;
}

void Nego::setOrigen(std::string origen) {
  this->origen_ = origen;
}

void Nego::setDestino(std::string destino) {
  this->destino_ = destino;
}

void Nego::setNumeroPlazas(int numeroPlazas) {
  this->numeroPlazas_ = numeroPlazas;
}

void Nego::setFecha(Fecha fecha) {
  this->fecha_ = fecha;
}

std::string Nego::getOrigen() {
  return this->origen_;
}

std::string Nego::getDestino() {
  return this->destino_;
}

int Nego::getNumeroPlazas() {
  return this->numeroPlazas_;
}

Fecha Nego::getFecha() {
  return this->fecha_;
}
