//AUTORES: Hugo Ferrando

#include <string>
#include "./owner.hpp"
#include "./nego.hpp"
#include "./pel_vector.hpp"

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
void Owner::setNombre(std::string nombre) { nombre_ = nombre; }

/**
 * @brief Owner::getNombre
 * @return
 */
std::string Owner::getNombre() { return nombre_; }
/**
 * @brief Owner::getOficinas
 * @return
 */
pel::vector<Oficina> &Owner::getOficinas() { return oficinas_; }
/**
 * @brief Owner::getNegos
 * @return
 */
pel::vector<std::shared_ptr<Nego>> &Owner::getNegos() { return negos_; }
