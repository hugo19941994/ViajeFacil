#ifndef PETICION_H
#define PETICION_H

#include "fecha.h"
#include <QString>

class Peticion
{
private:
	size_t id;
	QString origen;
	QString destino;
	Fecha fecha;
	size_t plazasPedidas;
public:
	Peticion();
	Peticion(size_t, QString, QString, Fecha, size_t);
	~Peticion();

	void setId(size_t);
	void setOrigen(QString);
	void setDestino(QString);
	void setFecha(Fecha);
	void setPlazasPedidas(size_t);

	size_t getId();
	QString getOrigen();
	QString getDestino();
	Fecha getFecha();
	size_t getPlazasPedidas();
};

#endif // PETICION_H
