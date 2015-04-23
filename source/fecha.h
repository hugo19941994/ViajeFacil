#ifndef FECHA_H
#define FECHA_H

#include <stddef.h>

class Fecha
{
private:
  std::size_t dia_;
  std::size_t mes_;
  int anio_; //Año puede ser negativo??

public:
  Fecha();
  Fecha(std::size_t dia, std::size_t mes, int anio);
  ~Fecha();

  void setFecha(std::size_t dia, size_t mes, int anio);
  void setDia(std::size_t dia);
  void setMes(std::size_t mes);
  void setAnio(int anio);

  std::size_t getDia();
  std::size_t getMes();
  int getAnio();

  //Quitar
  Fecha pedirFecha();
  void mostrarFecha(Fecha fecha);
};

#endif // FECHA_H
