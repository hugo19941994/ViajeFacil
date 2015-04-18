#include "negos.h"

negos::negos()
{
    this->origen="";
    this->destino="";
    this->id = 1;
    this->numeroPlazas=0;

    this->fecha = Fecha(1,1,1);
}

negos::negos(QString origen, QString destino, int id, int numeroPlazas, Fecha fecha)
{
    this->origen="";
    this->destino="";
    this->id = 1;
    this->numeroPlazas=0;

    this->fecha = Fecha(1,1,1);
}

negos::~negos()
{

}

void negos::setNego(QString origen, QString destino, int id, int numeroPlazas, Fecha fecha) {

}
