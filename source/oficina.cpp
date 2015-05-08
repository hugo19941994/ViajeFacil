#include <vector>
#include "./oficina.hpp"

Oficina::Oficina() : nombre_{""}, pais_{""}, continente_{""} {}

Oficina::Oficina(std::string nombre, std::string pais, std::string continente)
    : nombre_{nombre}, pais_{pais}, continente_{continente} {}

Oficina::~Oficina() {}

void Oficina::setNombre(std::string nombre) {
  this->nombre_ = nombre;
}

void Oficina::setPais(std::string pais) {
  this->pais_ = pais;
}

void Oficina::setContinente(std::string continente) {
  this->continente_ = continente;
}

std::string Oficina::getNombre() {
  return this->nombre_;
}

std::string Oficina::getPais() {
    return this->pais_;
}

std::string Oficina::getContinente() {
    return this->continente_;
}

std::vector<Peticion> &Oficina::getPeticiones() {
    return this->peticiones_;
}
