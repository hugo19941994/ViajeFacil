//AUTORES: Hugo Ferrando

#include <vector>
#include <string>
#include "./owner.hpp"
#include "./nego.hpp"

/**
 * @brief Owner::Owner
 */
Owner::Owner() : nombre_("") {}

/**
 * @brief Owner::Owner
 * @param nombre
 */
Owner::Owner(std::string nombre) : nombre_(nombre) {}

/**
 * @brief Owner::~Owner
 */
Owner::~Owner() {}

/**
 * @brief Owner::setNombre
 * @param nombre
 */
void Owner::setNombre(std::string nombre) { this->nombre_ = nombre; }

/**
 * @brief Owner::getNombre
 * @return
 */
std::string Owner::getNombre() { return this->nombre_; }
/**
 * @brief Owner::getOficinas
 * @return
 */
std::vector<Oficina> &Owner::getOficinas() { return this->oficinas_; }
/**
 * @brief Owner::getNegos
 * @return
 */
std::vector<Nego> &Owner::getNegos() { return this->negos_; }
