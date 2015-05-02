#ifndef FECHA_H
#define FECHA_H

#include <stddef.h>
#include "cereal/cereal.hpp"

class Fecha {
 private:
    std::size_t dia_;
    std::size_t mes_;
    int anio_;  // Anio puede ser negativo??

 public:
    Fecha();
    Fecha(std::size_t dia, std::size_t mes, int anio);
    ~Fecha();

    void setFecha(std::size_t dia, size_t mes, int anio);
    void setDia(std::size_t dia);
    void setMes(std::size_t mes);
    void setAnio(int anio);

    std::size_t getDia();
    std::size_t getMes();
    int getAnio();

    template<class Archive>
    void serialize(Archive & archive) {         // Serialize things by passing
        archive(cereal::make_nvp("Día", dia_),  // them the to the archive
        cereal::make_nvp("Mes", mes_),
        cereal::make_nvp("Año", anio_));
    }
    // Quitar
    Fecha pedirFecha();
    void mostrarFecha(Fecha fecha);
};

#endif  // FECHA_H
