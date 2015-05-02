#ifndef PETICION_H
#define PETICION_H

#include <QString>
#include "./fecha.hpp"
#include "./cereal/access.hpp"

class Peticion {
 private:
  std::size_t id_;
  QString origen_;
  QString destino_;
  Fecha fecha_;
  std::size_t plazasPedidas_;

 public:
  Peticion();
  Peticion(std::size_t id, QString origen, QString destino, Fecha fecha, std::size_t plazasPedidas);
  ~Peticion();

  void setId(std::size_t id);
  void setOrigen(QString origen);
  void setDestino(QString destino);
  void setFecha(Fecha fecha);
  void setPlazasPedidas(std::size_t plazasPedidas);

  std::size_t getId();
  QString getOrigen();
  QString getDestino();
  Fecha getFecha();
  std::size_t getPlazasPedidas();

  template<class Archive>
  void serialize(Archive & archive) {
        archive(cereal::make_nvp("Origen", origen_.toStdString()),
        cereal::make_nvp("Destino", destino_.toStdString()),
        cereal::make_nvp("Fecha",fecha_),
        cereal::make_nvp("Plazas Pedidas", plazasPedidas_)); // serialize things by passing them to the archive
  }
};

#endif  // PETICION_H
