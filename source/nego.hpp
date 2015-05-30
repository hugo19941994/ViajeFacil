/*DESCRIPCION:Los negos: una compañía crea negos, son los encargados de gestionar los paquetes
  y billetes aéreos, que le darán a los owners y estos a las oficinas correspondientes.
  AUTORES: David Jimenez y Hugo Ferrando
  */
#ifndef NEGO_H
#define NEGO_H

#include <string>
#include "./fecha.hpp"

/**
 * @brief The Nego class
 */
class Nego {
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
     * @brief numeroPlazas_
     */
    std::size_t numeroPlazas_;

    /**
     * @brief fecha_
     */
    Fecha fecha_;

 public:
    /**
     * @brief Nego
     */
    Nego();

    /**
     * @brief Nego
     * @param origen
     * @param destino
     * @param numeroPlazas
     * @param fecha
     */
    Nego(std::string origen, std::string destino,
         std::size_t numeroPlazas, Fecha fecha);

    ~Nego();
    /**
     * @brief setNego
     * @param origen
     * @param destino
     * @param numeroPlazas
     * @param fecha
     */
    void setNego(std::string origen, std::string destino,
        std::size_t numeroPlazas, Fecha fecha);

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
     * @brief setNumeroPlazas
     * @param numeroPlazas
     */
    void setNumeroPlazas(std::size_t numeroPlazas);

    /**
     * @brief setFecha
     * @param fecha
     */
    void setFecha(Fecha fecha);

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
     * @brief getNumeroPlazas
     * @return
     */
    std::size_t getNumeroPlazas();

    /**
     * @brief getFecha
     * @return
     */
    Fecha getFecha();

    /**
     * @brief serialize
     * @param archive
     */
    template<class Archive>  // Serialize things by passing them to the archive
    void serialize(Archive &archive) {
        archive(cereal::make_nvp("Origen", origen_),
            cereal::make_nvp("Destino", destino_),
            cereal::make_nvp("Numero_de_Plazas", numeroPlazas_),
            cereal::make_nvp("Fecha", fecha_));
    }
};

#endif  // NEGO_H
