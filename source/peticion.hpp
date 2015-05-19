/*DESCRIPCION: las peticiones son elaboradas por todas las partes de este proyecto, es decir, cada
 * acción que se realice va a ser una petición que se quedará guardada en esta clase "peticiones"
 * AUTORES: Sergio Candel, ayuda David Jimenez y Hugo Ferrando
 */
#ifndef PETICION_H
#define PETICION_H

#include <string>
#include "nego.hpp"
#include "./fecha.hpp"
#include "./cereal/access.hpp"

/**
 * @brief The Peticion class
 */
class Peticion {
 private:
  std::size_t plazasPedidas_;

 public:
  std::shared_ptr<Nego> neg; //PONERLO EN PRIVATE
  /**
   * @brief Peticion
   */
  Peticion();
  /**
   * @brief Peticion
   * @param plazasPedidas
   */
  Peticion(std::size_t plazasPedidas);

  ~Peticion();
  /**
   * @brief setPlazasPedidas
   * @param plazasPedidas
   */
  void setPlazasPedidas(std::size_t plazasPedidas);

  /**
   * @brief getPlazasPedidas
   * @return
   */
  std::size_t getPlazasPedidas();

  template<class Archive>  // serialize things by passing them to the archive
  /**
   * @brief serialize
   * @param archive
   */
  void serialize(Archive &archive) {
      /**
         * @brief archive
         */
        archive(cereal::make_nvp("Plazas Pedidas", plazasPedidas_),
        cereal::make_nvp("Nego", neg));
  }
};

#endif  // PETICION_H
