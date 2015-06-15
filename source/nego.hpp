/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author David Jiménez Cuevas
 *  @author Estefanía Ortego García
 *
 *  Los negos: una compañía crea negos, son los encargados de gestionar
 *  los paquetes y billetes aéreos, que le darán a los owners y estos
 *  a las oficinas correspondientes.
 */

#ifndef NEGO_H
#define NEGO_H

#include <string>
#include "./fecha.hpp"

/**
 *  @brief Clase Nego
 *  Un Nego es un vuelo concreto. Contiente Origen y Destino, unas Plazas,
 *  una Fecha concreta y pertenece a un único Owner.
 */
class Nego {
 private:
    std::string origen_;
    std::string destino_;
    std::size_t numeroPlazas_;
    Fecha fecha_;

 public:
    Nego();
    Nego(std::string origen, std::string destino,
         std::size_t numeroPlazas, Fecha fecha);
    ~Nego();

    void setNego(std::string origen, std::string destino,
        std::size_t numeroPlazas, Fecha fecha);
    void setOrigen(std::string origen);
    void setDestino(std::string destino);
    void setNumeroPlazas(std::size_t numeroPlazas);
    void setFecha(Fecha fecha);

    std::string getOrigen();
    std::string getDestino();
    std::size_t getNumeroPlazas();
    Fecha getFecha();

    /**
     * @brief devolverPlazas
     * Al borrar una peticion (o una oficina con peticiones), es necesario
     * devolver esas plazas que fueron asignadas al Nego que corresponda.
     */
    void devolverPlazas(std::size_t asientos);

    #ifdef CEREAL_CEREAL_HPP_
    /**
     * @brief Serializa con Cereal
     * Funcion para poder serializar Nego con Cereal
     */
    template<class Archive>
    void serialize(Archive& archive) {
        archive(cereal::make_nvp("Origen", origen_),
            cereal::make_nvp("Destino", destino_),
            cereal::make_nvp("Numero_de_Plazas", numeroPlazas_),
            cereal::make_nvp("Fecha", fecha_));
    }
    #endif
};

#endif  // NEGO_H
