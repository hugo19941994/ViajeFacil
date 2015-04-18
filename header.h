#ifndef HEADER_H
#define HEADER_H

#include <iostream>
#include <string>
#include "fecha.h"

const size_t MAXOWNERS = 10;
const size_t MAXNEGOS = 10;
const size_t MAXOFICINAS = 10;
const size_t MAXPETICIONES = 10;


typedef struct peticiones{
    int id = -1;
    std::string origen = "";
    std::string destino = "";
    Fecha fecha;
    int plazasPedidas = -1;
} peticiones;

typedef struct nego{
    std::string origen = "";
    std::string destino = "";
    int id = -1;
    int numeroPlazas = -1;
    Fecha fecha;
} nego;

typedef struct oficinas{
    std::string nombre = "";
    int id = -1;
    std::string pais = "";
    std::string continente = "";
    peticiones peticiones[MAXPETICIONES];
    int contPeticiones = 0;
    //string historial[1024];//[IdPeticion][Aceptada]
    int historial[1024];
    int contHistorial = 0;
} oficinas;

typedef struct owners{
    std::string nombre = "";
    int id = -1;
    oficinas oficinas[MAXOFICINAS];
    int contOficinas = 0;
    nego negos[MAXNEGOS];
    int contNegos = 0;
} owners;

nego* devolverNegos(owners *listaOwners, int* idOwner);
oficinas* devolverOficinas(owners *listaOwners, int* idOwner);
peticiones* devolverPeticiones(owners *listaOwners, int* idOwner, int *idOficina);

void menuNegos(owners *listaOwners);
void crearNego(owners *listaOwners);
void modificarNego(owners *listaOwners);
void consultarNegos(owners *listaOwners);
void borrarNego(owners *listaOwners);

void gestionarOficinas(owners *listaOwners);
void crearOficinas(owners *listaOwners);
void borrarOficinas(owners *listaOwners);
void consultarOficinas(owners *listaOwners);
void oficina(owners *listaOwners);

void crearPeticiones(owners *listaOwners);
void modificarPeticiones(owners *listaOwners);
void borrarPeticiones(owners *listaOwners);
void consultarLog(owners *listaOwners);
void mostrarPeticiones(owners *listaOwners);
bool resolucionPeticion(owners *listaOwners);

std::string mirar(int);

#endif
