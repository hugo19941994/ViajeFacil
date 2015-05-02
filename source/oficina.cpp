#include <vector>
#include "./oficina.hpp"

Oficina::Oficina() {
  this->nombre_ = "";
  this->id_ = -1;
  this->pais_ = "";
  this->continente_ = "";
  this->peticiones_.resize(1);
}

Oficina::Oficina(QString nombre, size_t id, QString pais, QString continente , std::size_t tPeticiones) {
  this->nombre_ = nombre;
  this->id_ = id;
  this->pais_ = pais;
  this->continente_ = continente;
  this->peticiones_.resize(tPeticiones);
}

Oficina::~Oficina() {
}

void Oficina::setNombre(QString nombre) {
  this->nombre_ = nombre;
}

void Oficina::setId(size_t id) {
  this->id_ = id;
}

void Oficina::setPais(QString pais) {
  this->pais_ = pais;
}

void Oficina::setContinente(QString continente) {
  this->continente_ = continente;
}

QString Oficina::getNombre() {
  return this->nombre_;
}

std::size_t Oficina::getId() {
    return this->id_;
}

QString Oficina::getPais() {
    return this->pais_;
}

QString Oficina::getContinente() {
    return this->continente_;
}

std::vector<Peticion> &Oficina::getPeticiones() { return this->peticiones_; }
