/**
 *  Copyright 2015 ViajeFacil
 *  @author Estefania Ortego
 *  @author Guillermo Gonzalez
 *  @author Hugo Ferrando Seage
 */

#include <string>
#include "./pelVector.hpp"
#include "./oficina.hpp"

Oficina::Oficina() : nombre_(""), pais_(""), continente_("") {}

Oficina::Oficina(std::string nombre, std::string pais, std::string continente)
    : nombre_(nombre), pais_(pais), continente_(continente) {}

Oficina::~Oficina() {}

void Oficina::setNombre(std::string nombre) { nombre_ = nombre; }
void Oficina::setPais(std::string pais) { pais_ = pais; }
void Oficina::setContinente(std::string continente) {
  continente_ = continente;
}

std::string Oficina::getNombre() { return nombre_; }
std::string Oficina::getPais() { return pais_; }
std::string Oficina::getContinente() { return continente_; }
pel::Vector<Peticion> &Oficina::getPeticiones() { return peticiones_; }
