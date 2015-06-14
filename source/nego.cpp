/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author David Jimenez Cuevas
 *  @author Estefanía Ortego García
 */

#include <string>
#include "./nego.hpp"

Nego::Nego()
    : origen_(""), destino_(""), numeroPlazas_(0), fecha_(Fecha(0, 0, 0)) {}


Nego::Nego(std::string origen, std::string destino,
    std::size_t numeroPlazas, Fecha fecha)
    : origen_(origen), destino_(destino),
    numeroPlazas_(numeroPlazas), fecha_(fecha) {}

Nego::~Nego() {}

void Nego::setNego(std::string origen, std::string destino,
    std::size_t numeroPlazas, Fecha fecha) {
  origen_ = origen;
  destino_ = destino;
  numeroPlazas_ = numeroPlazas;
  fecha_ = fecha;
}

void Nego::setOrigen(std::string origen) { origen_ = origen; }
void Nego::setDestino(std::string destino) { destino_ = destino; }
void Nego::setNumeroPlazas(std::size_t numeroPlazas) {
  numeroPlazas_ = numeroPlazas;
}
void Nego::setFecha(Fecha fecha) { fecha_ = fecha; }

std::string Nego::getOrigen() { return origen_; }
std::string Nego::getDestino() { return destino_; }
std::size_t Nego::getNumeroPlazas() { return numeroPlazas_; }
Fecha Nego::getFecha() { return fecha_; }

void Nego::devolverPlazas(std::size_t asientosN) { numeroPlazas_ += asientosN; }
