#ifndef OFICINA_H
#define OFICINA_H

#include <QString>
#include <vector>
#include "./peticion.hpp"

class Oficina {
 private:
  QString nombre_;
  QString pais_;
  QString continente_;
  std::vector<Peticion> peticiones_;

 public:
  Oficina();
  Oficina(QString nombre, QString pais,
      QString continente, std::size_t tPeticiones);
  ~Oficina();

  void setNombre(QString);
  void setPais(QString);
  void setContinente(QString);

  QString getNombre();
  QString getPais();
  QString getContinente();
  std::vector<Peticion> &getPeticiones();

  template<class Archive>  // Serialize things by passing them to the archive
    void serialize(Archive &archive) {
      archive(cereal::make_nvp("Nombre", nombre_.toStdString()),
        cereal::make_nvp("País", pais_.toStdString()),
        cereal::make_nvp("Continente", continente_.toStdString()),
        cereal::make_nvp("Peticiones", peticiones_));
    }
};

#endif  // OFICINA_H
