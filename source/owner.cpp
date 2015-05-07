#include <vector>
#include <string>
#include "./owner.hpp"
#include "./nego.hpp"

Owner::Owner() : nombre_{""} {}

Owner::Owner(std::string nombre) : nombre_{nombre} {}

Owner::~Owner() {}

void Owner::setNombre(std::string nombre) { this->nombre_ = nombre; }

std::string Owner::getNombre() { return this->nombre_; }

std::vector<Oficina> &Owner::getOficinas() { return this->oficinas_; }

std::vector<Nego> &Owner::getNegos() { return this->negos_; }
