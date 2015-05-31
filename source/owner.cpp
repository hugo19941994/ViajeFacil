/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 */

#include <string>
#include "./owner.hpp"
#include "./nego.hpp"
#include "./pelVector.hpp"

Owner::Owner() : nombre_("") {}
Owner::Owner(std::string nombre) : nombre_(nombre) {}
Owner::~Owner() {}

void Owner::setNombre(std::string nombre) { nombre_ = nombre; }

std::string Owner::getNombre() { return nombre_; }
pel::Vector<Oficina> &Owner::getOficinas() { return oficinas_; }
pel::Vector<std::shared_ptr<Nego>> &Owner::getNegos() { return negos_; }
