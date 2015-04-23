#ifndef PETICION_H
#define PETICION_H

#include <QString>
#include "fecha.h"

class Peticion
{
private:
	std::size_t id_;
	QString origen_;
	QString destino_;
	Fecha fecha_;
	std::size_t plazasPedidas_;
public:
	Peticion();
	Peticion(std::size_t id, QString origen, QString destino, Fecha fecha, std::size_t plazasPedidas);
	~Peticion();

	void setId(std::size_t id);
	void setOrigen(QString origen);
	void setDestino(QString destino);
	void setFecha(Fecha fecha);
	void setPlazasPedidas(std::size_t plazasPedidas);

	std::size_t getId();
	QString getOrigen();
	QString getDestino();
	Fecha getFecha();
	std::size_t getPlazasPedidas();
};

#endif // PETICION_H
