#ifndef OFICINA_H
#define OFICINA_H

#include <QString>
#include <vector>
#include "peticion.h"

class Oficina
{
private:
	QString nombre_;
	std::size_t id_;
	QString pais_;
	QString continente_;
	std::vector<Peticion> peticiones_;

public:
	Oficina();
	Oficina(QString nombre, std::size_t id, QString pais, QString continente, std::size_t tPeticiones);
	~Oficina();

	void setNombre(QString);
	void setId(std::size_t);
	void setPais(QString);
	void setContinente(QString);

	QString getNombre();
    std::size_t getId();
	QString getPais();
	QString getContinente();
    std::vector<Peticion> &getPeticiones();

};

#endif // OFICINA_H
