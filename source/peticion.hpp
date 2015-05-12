/*DESCRIPCION: las peticiones son elaboradas por todas las partes de este proyecto, es decir, cada
 * acción que se realice va a ser una petición que se quedará guardada en esta clase "peticiones"
 * AUTORES: Sergio Candel, ayuda David Jimenez y Hugo Ferrando
 */
#ifndef PETICION_H
#define PETICION_H

#include <string>
#include "./fecha.hpp"
#include "./cereal/access.hpp"

/**
 * @brief The Peticion class
 */
class Peticion {
 private:
    /**
   * @brief origen_
   */
  std::string origen_;
  /**
   * @brief destino_
   */
  std::string destino_;
  /**
   * @brief fecha_
   */
  Fecha fecha_;
  /**
   * @brief plazasPedidas_
   */
  std::size_t plazasPedidas_;

 public:
  /**
   * @brief Peticion
   */
  Peticion();
  /**
   * @brief Peticion
   * @param origen
   * @param destino
   * @param fecha
   * @param plazasPedidas
   */
  Peticion(std::string origen, std::string destino,
           /**
                * @brief fecha
                */
      Fecha fecha, std::size_t plazasPedidas);

  ~Peticion();
  /**
   * @brief setOrigen
   * @param origen
   */
  void setOrigen(std::string origen);
  /**
   * @brief setDestino
   * @param destino
   */
  void setDestino(std::string destino);
  /**
   * @brief setFecha
   * @param fecha
   */
  void setFecha(Fecha fecha);
  /**
   * @brief setPlazasPedidas
   * @param plazasPedidas
   */
  void setPlazasPedidas(std::size_t plazasPedidas);
  /**
   * @brief getOrigen
   * @return
   */
  std::string getOrigen();
  /**
   * @brief getDestino
   * @return
   */
  std::string getDestino();
  /**
   * @brief getFecha
   * @return
   */
  Fecha getFecha();
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
        archive(cereal::make_nvp("Origen", origen_),
                /**
                 * @brief cereal::make_nvp
                 */
        cereal::make_nvp("Destino", destino_),
                /**
                 * @brief cereal::make_nvp
                 */
        cereal::make_nvp("Fecha", fecha_),
        cereal::make_nvp("Plazas Pedidas", plazasPedidas_));
  }
};

#endif  // PETICION_H
