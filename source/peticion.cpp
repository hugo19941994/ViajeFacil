#include "./peticion.hpp"
#include "./fecha.hpp"

Peticion::Peticion() {
  this->id_ = -1;
  this->origen_ = "";
  this->destino_ = "";
  this->fecha_ = Fecha();
  this->plazasPedidas_ = -1;
}

Peticion::Peticion(size_t id, QString origen, QString destino, Fecha fecha, size_t plazasPedidas) {
  this->id_ = id;
  this->origen_ = origen;
  this->destino_ = destino;
  this->fecha_ = fecha;
  this->plazasPedidas_ = plazasPedidas;
}

Peticion::~Peticion() {
}

void Peticion::setId(size_t id) {
  this->id_ = id;
}

void Peticion::setOrigen(QString origen) {
  this->origen_ = origen;
}

void Peticion::setDestino(QString destino) {
  this->destino_ = destino;
}

void Peticion::setFecha(Fecha fecha) {
  this->fecha_ = fecha;
}

void Peticion::setPlazasPedidas(size_t plazasPedidas) {
  this->plazasPedidas_ = plazasPedidas;
}

size_t Peticion::getId() {
  return this->id_;
}

QString Peticion::getOrigen() {
  return this->origen_;
}

QString Peticion::getDestino() {
  return this->destino_;
}

Fecha Peticion::getFecha() {
  return this->fecha_;
}

size_t Peticion::getPlazasPedidas() {
  return this->plazasPedidas_;
}
