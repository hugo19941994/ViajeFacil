/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author Fernando Saavedra
 */

#ifndef FECHA_H
#define FECHA_H

#include <stddef.h>
#include "cereal/cereal.hpp"

/**
 * @brief Clase Fecha
 */
class Fecha {
 private:
    int dia_;
    int mes_;
    int anio_;

 public:
    Fecha();
    Fecha(int dia, int mes, int anio);
    ~Fecha();

    void setFecha(int dia, int mes, int anio);
    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

    int getDia();
    int getMes();
    int getAnio();

    #ifdef CEREAL_CEREAL_HPP_
    /**
     * @brief Serializa con Cereal
     * Funcion para poder serializar Fecha con Cereal
     */
    template<class Archive>
    void serialize(Archive & archive) {
        archive(cereal::make_nvp("Día", dia_),
        cereal::make_nvp("Mes", mes_),
        cereal::make_nvp("Año", anio_));
    }
    #endif
};

#endif  // FECHA_H
