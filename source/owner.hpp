/*DESCRIPCION:  Los owners: van a tener oficinas y negos (creado por la compañía).
 Son los que tienen oficinas que sirven de intermediario con los clientes, y gestionan
 las peticiones, les solicitan una serie de pasajes a los negos, los negos le dan unos
 billetes de avión o paquetes que los owners se encargan de responder esa petición a las oficinas.
 *AUTORES: Hugo Ferrando
 */
#ifndef OWNER_H
#define OWNER_H

#include <string>
#include "./nego.hpp"
#include "./oficina.hpp"
#include "./cereal/types/memory.hpp"

/**
 * @brief The Owner class
 */
class Owner {
 private:
    /**
   * @brief nombre_
   */
  std::string nombre_;
  /**
   * @brief negos_
   */
  pel::vector<std::shared_ptr<Nego>> negos_;
  /**
   * @brief oficinas_
   */
  pel::vector<Oficina> oficinas_;

 public:
  /**
   * @brief Owner
   */
  Owner();
  /**
   * @brief Owner
   * @param nombre
   */
  explicit Owner(std::string nombre);  // Entender que hace explicit mejor!
  ~Owner();
  /**
   * @brief setNombre
   */
  void setNombre(std::string);
  /**
   * @brief getNombre
   * @return
   */

  std::string getNombre();
  /**
   * @brief getNegos
   * @return
   */
  pel::vector<std::shared_ptr<Nego>> &getNegos();
  /**
   * @brief getOficinas
   * @return
   */
  pel::vector<Oficina> &getOficinas();

  template<class Archive>  // Serialize things by passing them to the archive
  /**
   * @brief serialize
   * @param archive
   */
  void serialize(Archive &archive) {
      /**
     * @brief archive
     */
    archive(cereal::make_nvp("Nombre", nombre_),
            /**
                 * @brief cereal::make_nvp
                 */
        cereal::make_nvp("Negos", negos_),
        cereal::make_nvp("Oficinas", oficinas_));
  }
};

#endif  // OWNER_H
