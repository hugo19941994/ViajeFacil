#include "./nego.hpp"

Nego::Nego() {
  this->origen_ = "";
  this->destino_ = "";
  this->id_ = -1;
  this->numeroPlazas_ = 0;
  this->fecha_ = Fecha(-1, -1, -1);
}

Nego::Nego(QString origen, QString destino, int id, int numeroPlazas, Fecha fecha) {
  this->origen_ = origen;
  this->destino_ = destino;
  this->id_ = id;
  this->numeroPlazas_ = numeroPlazas;
  this->fecha_ = fecha;
}

Nego::~Nego() {
  // delete this;
}

void Nego::setNego(QString origen, QString destino, int id, int numeroPlazas, Fecha fecha) {
  this->origen_ = origen;
  this->destino_ = destino;
  this->id_ = id;
  this->numeroPlazas_ = numeroPlazas;
  this->fecha_ = fecha;
}

void Nego::setOrigen(QString origen) {
  this->origen_ = origen;
}

void Nego::setDestino(QString destino) {
  this->destino_ = destino;
}

void Nego::setId(int id) {
  this->id_ = id;
}

void Nego::setNumeroPlazas(int numeroPlazas) {
  this->numeroPlazas_ = numeroPlazas;
}

void Nego::setFecha(Fecha fecha) {
  this->fecha_ = fecha;
}

QString Nego::getOrigen() {
  return this->origen_;
}

QString Nego::getDestino() {
  return this->destino_;
}

int Nego::getId() {
  return this->id_;
}

int Nego::getNumeroPlazas() {
  return this->numeroPlazas_;
}

Fecha Nego::getFecha() {
  return this->fecha_;
}
