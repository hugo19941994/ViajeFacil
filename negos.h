#ifndef NEGOS_H
#define NEGOS_H

#include <QString>
#include "fecha.h"

class negos
{

private:
    QString origen;
    QString destino;
    int id;
    int numeroPlazas;
    Fecha fecha;

//MIRAR LO DE CONST Y SUICIDARSE UN POCO
public:
    negos();
    negos(QString, QString, int, int, Fecha);
    ~negos();

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

    negos getNego(QString origen, QString destino, int id, int numeroPlazas, Fecha fecha);
};

#endif // NEGOS_H
