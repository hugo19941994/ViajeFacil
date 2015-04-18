#ifndef FECHA_H
#define FECHA_H

#include <cstdlib>

class Fecha
{
private:
  size_t dia;
  size_t mes;
  int anio;
public:
  Fecha();
  Fecha(size_t,size_t,int);
  ~Fecha();
  void setFecha(size_t pDia,size_t pMes, int pAnio);
  void setDia(size_t pDia);
  void setMes(size_t pMes);
  void setAnio(int pAnio);
  size_t getDia();
  size_t getMes();
  int getAnio();
  Fecha pedirFecha(); //Quitar
  void mostrarFecha(Fecha fecha);
};

#endif // FECHA_H
