#ifndef OFICINA_H
#define OFICINA_H

#include <vector>
#include <string>
#include "./peticion.hpp"

class Oficina {
 private:
  std::string nombre_;
  std::string pais_;
  std::string continente_;
  std::vector<Peticion> peticiones_;

 public:
  Oficina();
  Oficina(std::string nombre, std::string pais, std::string continente);
  ~Oficina();

  void setNombre(std::string);
  void setPais(std::string);
  void setContinente(std::string);

  std::string getNombre();
  std::string getPais();
  std::string getContinente();
  std::vector<Peticion> &getPeticiones();

  template<class Archive>  // Serialize things by passing them to the archive
    void serialize(Archive &archive) {
      archive(cereal::make_nvp("Nombre", nombre_),
        cereal::make_nvp("País", pais_),
        cereal::make_nvp("Continente", continente_),
        cereal::make_nvp("Peticiones", peticiones_));
    }
};

#endif  // OFICINA_H
