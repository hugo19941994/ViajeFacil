//AUTORES: Sergio Candel, ayuda David Jimenez y Hugo Ferrando


#include <string>
#include "./peticion.hpp"
#include "./fecha.hpp"

/**
 * @brief Peticion::Peticion
 */
Peticion::Peticion()
    : origen_(""), destino_(""), fecha_(Fecha(0, 0, 0)), plazasPedidas_(0) {}

/**
 * @brief Peticion::Peticion
 * @param origen
 * @param destino
 * @param fecha
 * @param plazasPedidas
 */
Peticion::Peticion(std::string origen, std::string destino,
    Fecha fecha, std::size_t plazasPedidas)
    : origen_(origen), destino_(destino),
    fecha_(fecha), plazasPedidas_(plazasPedidas) {}
/**
 * @brief Peticion::~Peticion
 */
Peticion::~Peticion() {}
/**
 * @brief Peticion::setOrigen
 * @param origen
 */
void Peticion::setOrigen(std::string origen) {
  this->origen_ = origen;
}
/**
 * @brief Peticion::setDestino
 * @param destino
 */
void Peticion::setDestino(std::string destino) {
  this->destino_ = destino;
}
/**
 * @brief Peticion::setFecha
 * @param fecha
 */
void Peticion::setFecha(Fecha fecha) {
  this->fecha_ = fecha;
}
/**
 * @brief Peticion::setPlazasPedidas
 * @param plazasPedidas
 */
void Peticion::setPlazasPedidas(size_t plazasPedidas) {
  this->plazasPedidas_ = plazasPedidas;
}
/**
 * @brief Peticion::getOrigen
 * @return
 */
std::string Peticion::getOrigen() {
  return this->origen_;
}
/**
 * @brief Peticion::getDestino
 * @return
 */
std::string Peticion::getDestino() {
  return this->destino_;
}
/**
 * @brief Peticion::getFecha
 * @return
 */
Fecha Peticion::getFecha() {
  return this->fecha_;
}
/**
 * @brief Peticion::getPlazasPedidas
 * @return
 */
size_t Peticion::getPlazasPedidas() {
  return this->plazasPedidas_;
}
