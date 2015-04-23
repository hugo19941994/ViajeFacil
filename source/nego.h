#ifndef NEGO_H
#define NEGO_H

#include <QString>
#include "fecha.h"

class Nego
{
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
};

#endif // NEGO_H
