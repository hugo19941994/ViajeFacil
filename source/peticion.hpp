/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author David Jimenez
 *  @author Serigo Cander
 *  las peticiones son elaboradas por todas las partes de este proyecto,
 *  es decir, cada acción que se realice va a ser una petición que
 *  se quedará guardada en esta clase "peticiones"
 */

#ifndef PETICION_H
#define PETICION_H

#include "./nego.hpp"
#include "./fecha.hpp"

/**
 * @brief The Peticion class
 */
class Peticion {
 private:
  std::size_t plazasPedidas_;

 public:
    std::shared_ptr<Nego> neg;  // PONERLO EN PRIVATE
    Peticion();
    explicit Peticion(std::size_t plazasPedidas);
    ~Peticion();
    void setPlazasPedidas(std::size_t plazasPedidas);
    std::size_t getPlazasPedidas();

    /**
    * @brief Serializa con Cereal
    * Funcion para poder serializar Owner con Cereal
    */
    #ifdef CEREAL_CEREAL_HPP_
    template<class Archive>  // serialize things by passing them to the archive
    void serialize(Archive &archive) {
        archive(cereal::make_nvp("Plazas Pedidas", plazasPedidas_),
        cereal::make_nvp("Nego", neg));
    }
    #endif
};

#endif  // PETICION_H
