// AUTORES: David Jimenez y Hugo Ferrando, ayuda Estefania ortego


#include "./nego.hpp"
#include <string>

/**
 * @brief Nego::Nego
 */
Nego::Nego()
    : origen_(""), destino_(""), numeroPlazas_(0), fecha_(Fecha(0, 0, 0)) {}

/**
 * @brief Nego::Nego
 * @param origen
 * @param destino
 * @param numeroPlazas
 * @param fecha
 */
Nego::Nego(std::string origen, std::string destino,
    std::size_t numeroPlazas, Fecha fecha)
    : origen_(origen), destino_(destino),
    numeroPlazas_(numeroPlazas), fecha_(fecha) {}
/**
 * @brief Nego::~Nego
 */
Nego::~Nego() {}

/**
 * @brief Nego::setNego
 * @param origen
 * @param destino
 * @param numeroPlazas
 * @param fecha
 */
void Nego::setNego(std::string origen, std::string destino,
    std::size_t numeroPlazas, Fecha fecha) {
  this->origen_ = origen;
  this->destino_ = destino;
  this->numeroPlazas_ = numeroPlazas;
  this->fecha_ = fecha;
}

//Funcion introducir origen en nego
/**
 * @brief Nego::setOrigen
 * @param origen
 */
void Nego::setOrigen(std::string origen) {
  this->origen_ = origen;
}

//Funcion introducir destino en nego
/**
 * @brief Nego::setDestino
 * @param destino
 */
void Nego::setDestino(std::string destino) {
  this->destino_ = destino;
}

/**
 * @brief Nego::setNumeroPlazas
 * @param numeroPlazas
 */
void Nego::setNumeroPlazas(std::size_t numeroPlazas) {
  this->numeroPlazas_ = numeroPlazas;
}
/**
 * @brief Nego::setFecha
 * @param fecha
 */
void Nego::setFecha(Fecha fecha) {
  this->fecha_ = fecha;
}

/**
 * @brief Nego::getOrigen
 * @return
 */
std::string Nego::getOrigen() {
  return this->origen_;
}

/**
 * @brief Nego::getDestino
 * @return
 */
std::string Nego::getDestino() {
  return this->destino_;
}

/**
 * @brief Nego::getNumeroPlazas
 * @return
 */
std::size_t Nego::getNumeroPlazas() {
  return this->numeroPlazas_;
}

/**
 * @brief Nego::getFecha
 * @return
 */
Fecha Nego::getFecha() {
  return this->fecha_;
}
