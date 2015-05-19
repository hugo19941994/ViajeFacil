//AUTORES: Sergio Candel, ayuda David Jimenez y Hugo Ferrando


#include <string>
#include "./peticion.hpp"
#include "./fecha.hpp"

/**
 * @brief Peticion::Peticion
 */
Peticion::Peticion()
    : plazasPedidas_(0) {}

/**
 * @brief Peticion::Peticion
 * @param plazasPedidas
 */
Peticion::Peticion(std::size_t plazasPedidas)
    : plazasPedidas_(plazasPedidas) {}
/**
 * @brief Peticion::~Peticion
 */
Peticion::~Peticion() {}

/**
 * @brief Peticion::setPlazasPedidas
 * @param plazasPedidas
 */
void Peticion::setPlazasPedidas(size_t plazasPedidas) {
  this->plazasPedidas_ = plazasPedidas;
}

/**
 * @brief Peticion::getPlazasPedidas
 * @return
 */
size_t Peticion::getPlazasPedidas() {
  return this->plazasPedidas_;
}
