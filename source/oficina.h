#ifndef OFICINA_H
#define OFICINA_H

#include <QString>

class Oficina
{
private:
	QString nombre;
	size_t id;
	QString pais;
	QString continente;
	//peticiones peticiones[MAXPETICIONES];
	//int contPeticiones;
	//int historial[1024];
	//int contHistorial = 0;

public:
	Oficina();
	Oficina(QString, size_t, QString, QString);
	~Oficina();

	void setNombre(QString);
	void setId(size_t);
	void setPais(QString);
	void setContinente(QString);

	QString getNombre();
	int getId();
	QString getPais();
	QString getContinente();
};

#endif // OFICINA_H
