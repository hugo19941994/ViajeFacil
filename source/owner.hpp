#ifndef OWNER_H
#define OWNER_H

#include <QString>
#include <vector>
#include "./nego.hpp"
#include "./oficina.hpp"
#include "./cereal/access.hpp"

class Owner {
 private:
  QString nombre_;
  std::size_t id_;  // Necesario?
  std::vector<Nego> negos_;
  std::vector<Oficina> oficinas_;
 public:
  Owner();
  Owner(QString nombre, std::size_t id, std::size_t tNegos, std::size_t tOficinas);
  ~Owner();

  void setNombre(QString);
  void setId(std::size_t);

  QString getNombre();
  std::size_t getID();

  std::vector<Nego> &getNegos();
  std::vector<Oficina> &getOficinas();

  template<class Archive>
  void serialize(Archive & archive) {
    archive(cereal::make_nvp("Nombre", nombre_.toStdString()),
        cereal::make_nvp("Negos", negos_),
        cereal::make_nvp("Oficinas", oficinas_)); // serialize things by passing them to the archive
  }
};

#endif  // OWNER_H
