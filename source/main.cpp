/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 *  @author David Jimenez Cuevas
 *  @author Estefanía Ortego García
 *  @author Guillermo González Moreno
 *  @author Fernando Saavedra Hernández
 *  @author Sergio Candel
 *  Website: https://github.com/hugo19941994/ViajeFacil
 */

#define CATCH_CONFIG_RUNNER

#include <QApplication>
#include "./mainWindow.hpp"
#include "./catch/catch.hpp"

int main(int argc, char *argv[]) {
    #ifdef EXEC_TEST
    Catch::Session().run(argc, argv);
    #endif

    QApplication a(argc, argv);
    mainWindow w;
    w.show();

    return a.exec();
}
