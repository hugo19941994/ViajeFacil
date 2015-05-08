#ifndef NEGO_H
#define NEGO_H

#include <string>
#include "./fecha.hpp"

class Nego {
 private:
    std::string origen_;
    std::string destino_;
    int numeroPlazas_;
    Fecha fecha_;

 public:
    Nego();
    Nego(std::string origen, std::string destino,
         int numeroPlazas, Fecha fecha);
    ~Nego();

    void setNego(std::string origen, std::string destino,
        int numeroPlazas, Fecha fecha);
    void setOrigen(std::string origen);
    void setDestino(std::string destino);
    void setNumeroPlazas(int numeroPlazas);
    void setFecha(Fecha fecha);

    std::string getOrigen();
    std::string getDestino();
    int getNumeroPlazas();
    Fecha getFecha();

    template<class Archive>  // Serialize things by passing them to the archive
    void serialize(Archive &archive) {
        archive(cereal::make_nvp("Origen", origen_),
            cereal::make_nvp("Destino", destino_),
            cereal::make_nvp("Numero_de_Plazas", numeroPlazas_),
            cereal::make_nvp("Fecha", fecha_));
    }
};

#endif  // NEGO_H
