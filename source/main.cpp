/*
Proyecto:  Unisys 2015
Titulo:    Viaje Facil
Miembros:  David Jiménez Cuevas
      Hugo Ferrando Seage
      Guillermo González Moreno
      Fernando Saavedra Hernández
      Estefanía Ortego García
Web: https://github.com/hugo19941994/ViajeFacil
Descripcion:
  Owners:    Compañias de vuelo (Iberia, Halcon Viajes)
  Negos:    Paquetes de vuelo
  Oficinas:  Sucursales de Owners
  Peticiones:  Viajes que piden las oficinas
TODO:
  Hay que hacer que cuando se aproxime a la fecha del vuelo, se
  le quite un 20% de peticiones a las oficinas
  El log de peticiones
*/

#include <QApplication>
#include "./mainWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    mainWindow w;
    w.show();

    return a.exec();
}
