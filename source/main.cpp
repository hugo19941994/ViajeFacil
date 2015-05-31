/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author David Jimenez
 *  @author Estefanía Ortego García
 *  @author Guillermo González Moreno
 *  @author Fernando Saavedra Hernández
 *  @author Sergio Candel
 *  Website: https://github.com/hugo19941994/ViajeFacil
 */

#include <QApplication>
#include "./mainWindow.hpp"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    mainWindow w;
    w.show();

    return a.exec();
}
