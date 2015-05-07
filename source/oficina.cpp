#include <vector>
#include "./oficina.hpp"

Oficina::Oficina() {
  this->nombre_ = "";
  this->pais_ = "";
  this->continente_ = "";
}

Oficina::Oficina(QString nombre, QString pais,
    QString continente , std::size_t tPeticiones) {
  this->nombre_ = nombre;
  this->pais_ = pais;
  this->continente_ = continente;
  this->peticiones_.resize(tPeticiones);
}

Oficina::~Oficina() {}

void Oficina::setNombre(QString nombre) {
  this->nombre_ = nombre;
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

QString Oficina::getPais() {
    return this->pais_;
}

QString Oficina::getContinente() {
    return this->continente_;
}

std::vector<Peticion> &Oficina::getPeticiones() {
    return this->peticiones_;
}
