#ifndef PETICION_H
#define PETICION_H

#include <string>
#include "./fecha.hpp"
#include "./cereal/access.hpp"

class Peticion {
 private:
  std::string origen_;
  std::string destino_;
  Fecha fecha_;
  std::size_t plazasPedidas_;

 public:
  Peticion();
  Peticion(std::string origen, std::string destino,
      Fecha fecha, std::size_t plazasPedidas);
  ~Peticion();

  void setOrigen(std::string origen);
  void setDestino(std::string destino);
  void setFecha(Fecha fecha);
  void setPlazasPedidas(std::size_t plazasPedidas);

  std::string getOrigen();
  std::string getDestino();
  Fecha getFecha();
  std::size_t getPlazasPedidas();

  template<class Archive>  // serialize things by passing them to the archive
  void serialize(Archive &archive) {
        archive(cereal::make_nvp("Origen", origen_),
        cereal::make_nvp("Destino", destino_),
        cereal::make_nvp("Fecha", fecha_),
        cereal::make_nvp("Plazas Pedidas", plazasPedidas_));
  }
};

#endif  // PETICION_H
