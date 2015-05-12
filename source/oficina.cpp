//*AUTORES: Estefania Ortego y Guillermo Gonzalez

#include <vector>
#include "./oficina.hpp"

/**
 * @brief Oficina::Oficina
 */
Oficina::Oficina() : nombre_(""), pais_(""), continente_("") {}

/**
 * @brief Oficina::Oficina
 * @param nombre
 * @param pais
 * @param continente
 */
Oficina::Oficina(std::string nombre, std::string pais, std::string continente)
    : nombre_(nombre), pais_(pais), continente_(continente) {}

/**
 * @brief Oficina::~Oficina
 */
Oficina::~Oficina() {}

/**
 * @brief Oficina::setNombre
 * @param nombre
 */
void Oficina::setNombre(std::string nombre) {
  this->nombre_ = nombre;
}

/**
 * @brief Oficina::setPais
 * @param pais
 */
void Oficina::setPais(std::string pais) {
  this->pais_ = pais;
}

/**
 * @brief Oficina::setContinente
 * @param continente
 */
void Oficina::setContinente(std::string continente) {
  this->continente_ = continente;
}

/**
 * @brief Oficina::getNombre
 * @return
 */
std::string Oficina::getNombre() {
  return this->nombre_;
}

/**
 * @brief Oficina::getPais
 * @return
 */
std::string Oficina::getPais() {
    return this->pais_;
}

/**
 * @brief Oficina::getContinente
 * @return
 */
std::string Oficina::getContinente() {
    return this->continente_;
}

/**
 * @brief Oficina::getPeticiones
 * @return
 */
std::vector<Peticion> &Oficina::getPeticiones() {
    return this->peticiones_;
}
