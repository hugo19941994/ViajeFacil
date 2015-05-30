/*DESCRIPCION:Las oficinas: se encargan de intermediar con los clientes, recaudar dinero,
 hacer ofertas para que los clientes compren en esa compañía. Estos, le solicitan billetes
 a los owners, y los owners a los negos, enviandole( los owners) como respuesta si es aceptada
 la petición o rechazada.
 *AUTORES: Estefania Ortego y Guillermo Gonzalez
 */
#ifndef OFICINA_H
#define OFICINA_H

#include <string>
#include "./pel_vector.hpp"
#include "./peticion.hpp"  // las oficinas crean peticiones, se necesitará acceso a los datos de las peticiones

// Clase oficina
/**
 * @brief The Oficina class
 */
class Oficina {
 private:  // Datos que tendrá la clase oficina
    /**
   * @brief nombre_
   */
  std::string nombre_;

  /**
   * @brief pais_
   */
  std::string pais_;

  /**
   * @brief continente_
   */
  std::string continente_;

  /**
   * @brief peticiones_
   */
  pel::vector<Peticion> peticiones_;

 public:  // Funciones que realizará esta clase
  /**
   * @brief Oficina
   */
  Oficina();  // Constructor

  /**
   * @brief Oficina
   * @param nombre
   * @param pais
   * @param continente
   */
  Oficina(std::string nombre, std::string pais, std::string continente);

  ~Oficina();  // destructor

  /**
   * @brief setNombre
   * Datos a introducir por el usuario
   */
  void setNombre(std::string);

  /**
   * @brief setPais
   */
  void setPais(std::string);

  /**
   * @brief setContinente
   */
  void setContinente(std::string);

  // El programa devolverá los datos introducidos pertenecientes a oficina
  /**
   * @brief getNombre
   * @return
   */
  std::string getNombre();

  /**
   * @brief getPais
   * @return
   */
  std::string getPais();

  /**
   * @brief getContinente
   * @return
   */
  std::string getContinente();

  /**
   * @brief getPeticiones
   * @return
   */
  pel::vector<Peticion> &getPeticiones();

  /**
     * @brief serialize
     * @param archive
     */
  template<class Archive>  // Serialize things by passing them to the archive
  void serialize(Archive &archive) {
      archive(cereal::make_nvp("Nombre", nombre_),
        cereal::make_nvp("País", pais_),
        cereal::make_nvp("Continente", continente_),
        cereal::make_nvp("Peticiones", peticiones_));
    }
};

#endif  // OFICINA_H
