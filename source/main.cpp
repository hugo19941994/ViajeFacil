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
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file

#include <QApplication>
#include "./mainWindow.hpp"
#include "./catch/catch.hpp"

unsigned int Factorial( unsigned int number ) {
    return number <= 1 ? number : Factorial(number-1)*number;
}

TEST_CASE( "Factorials are computed", "[factorial]" ) {
    REQUIRE( Factorial(1) == 1 );
    REQUIRE( Factorial(2) == 2 );
    REQUIRE( Factorial(3) == 6 );
    REQUIRE( Factorial(10) == 3628800 );
}

int main(int argc, char *argv[]) {
    int result = Catch::Session().run( argc, argv );
    QApplication a(argc, argv);
    mainWindow w;
    w.show();

    return a.exec();
}
