//AUTORES: Fernando Saavedra

#include "./fecha.hpp"

/**
 * @brief Fecha::Fecha
 */
Fecha::Fecha() : dia_(0), mes_(0), anio_(0) {}

/**
 * @brief Fecha::Fecha
 * @param dia
 * @param mes
 * @param anio
 */
Fecha::Fecha(size_t dia, size_t mes, int anio)
    : dia_(dia), mes_(mes), anio_(anio) {}

/**
 * @brief Fecha::~Fecha
 */
Fecha::~Fecha() {}

/**
 * @brief Fecha::setFecha
 * @param dia
 * @param mes
 * @param anio
 * Datos fecha
 */
void Fecha::setFecha(size_t dia, size_t mes, int anio) {
  dia_ = dia;
  mes_ = mes;
  anio_ = anio;
}

/**
 * @brief Fecha::setDia
 * @param dia
 */
void Fecha::setDia(size_t dia) {
  dia_ = dia;
}

/**
 * @brief Fecha::setMes
 * @param mes
 */
void Fecha::setMes(size_t mes) {
  mes_ = mes;
}

/**
 * @brief Fecha::setAnio
 * @param anio
 */
void Fecha::setAnio(int anio) {
  anio_ = anio;
}

/**
 * @brief Fecha::getDia
 * @return
 */
size_t Fecha::getDia() {
  return dia_;
}

/**
 * @brief Fecha::getMes
 * @return
 */
size_t Fecha::getMes() {
  return mes_;
}

/**
 * @brief Fecha::getAnio
 * @return
 */
int Fecha::getAnio() {
  return anio_;
}
