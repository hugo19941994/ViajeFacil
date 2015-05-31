/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author David Jimenez
 *  @author Serigo Cander
 */

#include "./peticion.hpp"
#include "./fecha.hpp"

Peticion::Peticion()
    : plazasPedidas_(0) {}

Peticion::Peticion(std::size_t plazasPedidas)
    : plazasPedidas_(plazasPedidas) {}

Peticion::~Peticion() {}

void Peticion::setPlazasPedidas(size_t plazasPedidas) {
    plazasPedidas_ = plazasPedidas;
}

size_t Peticion::getPlazasPedidas() { return plazasPedidas_; }
