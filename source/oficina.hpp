/**
 *  Copyright 2015 ViajeFacil
 *  @author Estefania Ortego
 *  @author Guillermo Gonzalez
 *  @author Hugo Ferrando Seage
 *
 *  Las oficinas: se encargan de intermediar con los clientes, recaudar dinero,
 *  hacer ofertas para que los clientes compren en esa compañía. Estos, le
 *  solicitan billetes a los owners, y los owners a los negos, enviandole
 *  (los owners) como respuesta si es aceptada la petición o rechazada.
 */

#ifndef OFICINA_H
#define OFICINA_H

#include <string>
#include "./pelVector.hpp"
#include "./peticion.hpp"

class Oficina {
 private:
  std::string nombre_;
  std::string pais_;
  std::string continente_;
  pel::Vector<Peticion> peticiones_;

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
  pel::Vector<Peticion> &getPeticiones();

  template<class Archive>
  void serialize(Archive &archive) {
      archive(cereal::make_nvp("Nombre", nombre_),
        cereal::make_nvp("País", pais_),
        cereal::make_nvp("Continente", continente_),
        cereal::make_nvp("Peticiones", peticiones_));
    }
};

#endif  // OFICINA_H
