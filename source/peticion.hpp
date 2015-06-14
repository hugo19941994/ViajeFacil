/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author David Jimenez Cuevas
 *  @author Serigo Candel
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
    std::shared_ptr<Nego> neg;

 public:
    Peticion();
    explicit Peticion(std::size_t plazasPedidas);
    ~Peticion();
    void setPlazasPedidas(std::size_t plazasPedidas);
    std::size_t getPlazasPedidas();

    #ifdef CEREAL_CEREAL_HPP_
    /**
    * @brief Serializa con Cereal
    * Funcion para poder serializar Owner con Cereal
    */
    template<class Archive>  // serialize things by passing them to the archive
    void serialize(Archive &archive) {
        archive(cereal::make_nvp("Plazas Pedidas", plazasPedidas_),
        cereal::make_nvp("Nego", neg));
    }
    #endif
    std::shared_ptr<Nego> getNeg() const;
    void setNeg(const std::shared_ptr<Nego> &value);
};

#endif  // PETICION_H
