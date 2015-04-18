#ifndef OWNER_H
#define OWNER_H

#include <QString>

class Owner
{
private:
	QString nombre;
	size_t id;
	//oficinas oficinas[MAXOFICINAS];
	//int contOficinas;
	//nego negos[MAXNEGOS];
	//int contNegos = 0;
public:
	Owner();
	Owner(QString, size_t);
	~Owner();

	void setNombre(QString);
	void setId(size_t);

	QString getNombre();
	size_t getID();
};

#endif // OWNER_H
