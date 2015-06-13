/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 */

#include "./catch/catch.hpp"
#include "./pelVector.hpp"
#include "./owner.hpp"
#include "./nego.hpp"
#include "./entradaHistorial.hpp"

TEST_CASE("Pushing ints to pelVector", "[pelVector]") {
    pel::Vector<int> v;
    v.push_back(1);
    REQUIRE(v.size() == 1);
    v.push_back(2);
    REQUIRE(v.size() == 2);
    v.popBack();
    REQUIRE(v.size() == 1);
    v.popBack();
    REQUIRE(v.empty() == true);
}

TEST_CASE("Pushing Owners to pelVector", "[pelVector]") {
    Owner o1 {"Halcon"};
    Owner o2 {"ECE"};
    pel::Vector<Owner> v;
    v.push_back(o1);
    REQUIRE(v.size() == 1);
    v.push_back(o2);
    REQUIRE(v.size() == 2);
    v.popBack();
    REQUIRE(v.size() == 1);
    v.popBack();
    REQUIRE(v.empty() == true);
}

TEST_CASE("Crear Owner completo", "[Owner]") {
    Owner o1 {"Halcon"};
    Nego n1 {};
    n1.setNumeroPlazas(20);
    o1.getNegos().push_back(std::make_shared<Nego>(n1));
    Oficina of1 {};
    o1.getOficinas().push_back(of1);
    Peticion p1{};
    p1.setNeg(std::shared_ptr<Nego>(o1.getNegos().at(0)));
    p1.setPlazasPedidas(10);
    o1.getOficinas().at(0).getPeticiones().push_back(p1);

    if (static_cast<int>(p1.getNeg()->getNumeroPlazas() -
                         p1.getPlazasPedidas()) >= 0)
        p1.getNeg()->setNumeroPlazas(p1.getNeg()->getNumeroPlazas() -
                                 p1.getPlazasPedidas());

    REQUIRE(o1.getNegos().at(0)->getNumeroPlazas() == 10);
}

TEST_CASE("Leer/Escribir en archivo el historial", "[entradaHistorial]") {
    entradaHistorial h1{};
    entradaHistorial h2{};
    h2.setOwner("pepe");
    pel::Vector<entradaHistorial> v = {h1, h2};
    v.writeToFile("testHistorial.txt");
    pel::Vector<entradaHistorial> v2;

    v2.readFromFile("testHistorial.txt");

    REQUIRE(v2.at(1).getOwner() == "pepe");
}
