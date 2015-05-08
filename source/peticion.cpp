#include <string>
#include "./peticion.hpp"
#include "./fecha.hpp"

Peticion::Peticion()
    : origen_(""), destino_(""), fecha_(Fecha(0, 0, 0)), plazasPedidas_(0) {}

Peticion::Peticion(std::string origen, std::string destino,
    Fecha fecha, std::size_t plazasPedidas)
    : origen_(origen), destino_(destino),
    fecha_(fecha), plazasPedidas_(plazasPedidas) {}

Peticion::~Peticion() {}

void Peticion::setOrigen(std::string origen) {
  this->origen_ = origen;
}

void Peticion::setDestino(std::string destino) {
  this->destino_ = destino;
}

void Peticion::setFecha(Fecha fecha) {
  this->fecha_ = fecha;
}

void Peticion::setPlazasPedidas(size_t plazasPedidas) {
  this->plazasPedidas_ = plazasPedidas;
}

std::string Peticion::getOrigen() {
  return this->origen_;
}

std::string Peticion::getDestino() {
  return this->destino_;
}

Fecha Peticion::getFecha() {
  return this->fecha_;
}

size_t Peticion::getPlazasPedidas() {
  return this->plazasPedidas_;
}
