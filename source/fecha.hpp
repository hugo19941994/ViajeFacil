/*DESCRIPCION: se crea una clase fecha que se utilizará en gran parte del programa, para mostrar fechas
 * de los pasajes disponibles.
 * AUTORES: Fernando Saavedra
 */
#ifndef FECHA_H
#define FECHA_H

#include <stddef.h>
#include "cereal/cereal.hpp"

/**
 * @brief The Fecha class
 */
class Fecha {
 private:
    /**
     * @brief dia_
     */
    std::size_t dia_;

    /**
     * @brief mes_
     */
    std::size_t mes_;

    /**
     * @brief anio_
     */
    int anio_;  // Anio puede ser negativo??

 public:
    /**
     * @brief Fecha
     */
    Fecha();
    /**
     * @brief Fecha
     * @param dia
     * @param mes
     * @param anio
     */
    Fecha(std::size_t dia, std::size_t mes, int anio);

    ~Fecha(); // Destructor, se podrá reiniciar la introduccion de la fecha

    /**
     * @brief setFecha
     * @param dia
     * @param mes
     * @param anio
     */
    void setFecha(std::size_t dia, std::size_t mes, int anio); // en fecha se eligen los valores(dia,mes,año)

    /**
     * @brief setDia
     * @param dia
     */
    void setDia(std::size_t dia);

    /**
     * @brief setMes
     * @param mes
     */
    void setMes(std::size_t mes);

    /**
     * @brief setAnio
     * @param anio
     */
    void setAnio(int anio);

    /**
     * @brief getDia
     * @return
     * Se devuelven los valores elegidos por el usuario(dia, mes, año)
     */
    std::size_t getDia();

    /**
     * @brief getMes
     * @return
     */
    std::size_t getMes();

    /**
     * @brief getAnio
     * @return
     */
    int getAnio();

    /**
     * @brief serialize
     * @param archive
     */
    template<class Archive>  // Serialize things by passing them to the archive
    void serialize(Archive & archive) {
        archive(cereal::make_nvp("Día", dia_),
        cereal::make_nvp("Mes", mes_),
        cereal::make_nvp("Año", anio_));
    }
};

#endif  // FECHA_H
