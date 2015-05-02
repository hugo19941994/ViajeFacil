#ifndef NEGO_H
#define NEGO_H

#include <QString>
#include "./fecha.hpp"

class Nego {
 private:
    QString origen_;
    QString destino_;
    int id_;
    int numeroPlazas_;
    Fecha fecha_;

 public:
    Nego();
	  Nego(QString origen, QString destino, int id, int numeroPlazas, Fecha fecha);
    ~Nego();

    void setNego(QString origen, QString destino, int id, int numeroPlazas, Fecha fecha);
    void setOrigen(QString origen);
    void setDestino(QString destino);
    void setId(int id);
    void setNumeroPlazas(int numeroPlazas);
    void setFecha(Fecha fecha);

    QString getOrigen();
    QString getDestino();
    int getId();
    int getNumeroPlazas();
    Fecha getFecha();

    template<class Archive>
    void serialize(Archive & archive) {
        archive(cereal::make_nvp("Origen", origen_.toStdString()),
            cereal::make_nvp("Destino", destino_.toStdString()),
            cereal::make_nvp("Numero de Plazas", numeroPlazas_),
            cereal::make_nvp("Fecha", fecha_)); // serialize things by passing them to the archive
    }
};

#endif  // NEGO_H
