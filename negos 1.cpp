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










void Fecha::setFecha(size_t pDia,size_t pMes,int pAnio){
  this->dia = pDia;
  this->mes = pMes;
  this->anio = pAnio;
}
void Fecha::setDia(size_t pDia){
  this->dia = pDia;
}
void Fecha::setMes(size_t pMes){
  this->mes = pMes;
}
void Fecha::setAnio(int pAnio){
  this->dia = pAnio;
}
size_t Fecha::getDia() {
  return this->dia;
}
size_t Fecha::getMes() {
  return this->mes;
}
int Fecha::getAnio() {
  return this->anio;
}
