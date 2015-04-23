#ifndef OWNER_H
#define OWNER_H

#include <QString>
#include <vector>
#include "nego.h"
#include "oficina.h"

class Owner
{
private:
	QString nombre_;
	std::size_t id_; //Necesario?
	std::vector<Nego> negos_;
	std::vector<Oficina> oficinas_;
public:
	Owner();
	Owner(QString nombre, std::size_t id, std::size_t tNegos, std::size_t tOficinas);
	~Owner();

	void setNombre(QString);
	void setId(std::size_t);

	QString getNombre();
	std::size_t getID();
	std::vector<Nego>* getNegos(); //Ver como implementar
	std::vector<Oficina>* getOficinas();
};

#endif // OWNER_H
