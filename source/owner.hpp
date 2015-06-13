/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *
 *  Los owners: van a tener oficinas y negos (creado por la compañía).
 *  Son los que tienen oficinas que sirven de intermediario con los
 *  clientes, y gestionan las peticiones, les solicitan una serie de
 *  pasajes a los negos, los negos le dan unos billetes de avión o paquetes
 *  que los owners se encargan de responder esa petición a las oficinas.
 */

#ifndef OWNER_H
#define OWNER_H

#include <string>
#include "pelVector.hpp"
#include "./nego.hpp"
#include "./oficina.hpp"
#include "./cereal/types/memory.hpp"

/**
 * @brief Clase Owner
 */
class Owner {
 private:
    std::string nombre_;
    pel::Vector<std::shared_ptr<Nego>> negos_;
    pel::Vector<Oficina> oficinas_;

 public:
    Owner();
    explicit Owner(std::string nombre);  // Entender que hace explicit mejor!
    ~Owner();

    void setNombre(std::string);
    std::string getNombre();

    pel::Vector<std::shared_ptr<Nego>> &getNegos();
    pel::Vector<Oficina> &getOficinas();

    /**
    * @brief Serializa con Cereal
    * Funcion para poder serializar Owner con Cereal
    */
    template<class Archive>
    void serialize(Archive &archive) {
    archive(cereal::make_nvp("Nombre", nombre_),
        cereal::make_nvp("Negos", negos_),
        cereal::make_nvp("Oficinas", oficinas_));
    }
};

#endif  // OWNER_H
