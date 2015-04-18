#ifndef NEGO_H
#define NEGO_H

#include "fecha.h"
#include <QString>

class Nego
{
private:
    QString origen;
    QString destino;
    int id;
    int numeroPlazas;
    Fecha fecha;

public:
    Nego();
    Nego(QString, QString, int, int, Fecha);
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
