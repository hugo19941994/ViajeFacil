#include "owner.h"
#include "nego.h"

Owner::Owner(){
	this->nombre_ = "";
	this->id_ = -1;
	this->negos_.resize(0);
}

Owner::Owner(QString nombre, std::size_t id, std::size_t tNegos, std::size_t tOficinas){
	this->nombre_ = nombre;
	this->id_ = id;
	this->negos_.resize(tNegos); //Asegurarse de que esto esta bien!
	this->negos_.resize(tOficinas);
}

Owner::~Owner(){

}

void Owner::setNombre(QString nombre){
	this->nombre_ = nombre;
}

void Owner::setId(std::size_t id){
	this->id_ = id;
}

QString Owner::getNombre(){
	return this->nombre_;
}

std::size_t Owner::getID(){
	return this->id_;
}

//Implementar
//std::vector<Nego>& getNegos(){
//	return this->negos_;
//}
//
//std::vector<Oficina>& getOficinas(){
//	return this->oficina_;
//}