#ifndef OWNER_H
#define OWNER_H

#include <vector>
#include <string>
#include "./nego.hpp"
#include "./oficina.hpp"
#include "./cereal/access.hpp"

class Owner {
 private:
  std::string nombre_;
  std::vector<Nego> negos_;
  std::vector<Oficina> oficinas_;

 public:
  Owner();
  explicit Owner(std::string nombre);  // Entender que hace explicit mejor!
  ~Owner();

  void setNombre(std::string);

  std::string getNombre();

  std::vector<Nego> &getNegos();
  std::vector<Oficina> &getOficinas();

  template<class Archive>  // Serialize things by passing them to the archive
  void serialize(Archive &archive) {
    archive(cereal::make_nvp("Nombre", nombre_),
        cereal::make_nvp("Negos", negos_),
        cereal::make_nvp("Oficinas", oficinas_));
  }
};

#endif  // OWNER_H
