// AUTORES: David Jimenez y Hugo Ferrando, ayuda Estefania ortego

#include <string>
#include "./nego.hpp"

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
  origen_ = origen;
  destino_ = destino;
  numeroPlazas_ = numeroPlazas;
  fecha_ = fecha;
}

/**
 * @brief Nego::setOrigen
 * @param origen
 * Funcion introducir origen en nego
 */
void Nego::setOrigen(std::string origen) {
  origen_ = origen;
}

/**
 * @brief Nego::setDestino
 * @param destino
 * Funcion introducir destino en nego
 */
void Nego::setDestino(std::string destino) {
  destino_ = destino;
}

/**
 * @brief Nego::setNumeroPlazas
 * @param numeroPlazas
 */
void Nego::setNumeroPlazas(std::size_t numeroPlazas) {
  numeroPlazas_ = numeroPlazas;
}

/**
 * @brief Nego::setFecha
 * @param fecha
 */
void Nego::setFecha(Fecha fecha) {
  fecha_ = fecha;
}

/**
 * @brief Nego::getOrigen
 * @return
 */
std::string Nego::getOrigen() {
  return origen_;
}

/**
 * @brief Nego::getDestino
 * @return
 */
std::string Nego::getDestino() {
  return destino_;
}

/**
 * @brief Nego::getNumeroPlazas
 * @return
 */
std::size_t Nego::getNumeroPlazas() {
  return numeroPlazas_;
}

/**
 * @brief Nego::getFecha
 * @return
 */
Fecha Nego::getFecha() {
  return fecha_;
}
