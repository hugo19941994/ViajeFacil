/**
 *  Copyright 2015 ViajeFacil
 *  @author Hugo Ferrando Seage
 */

#ifndef ENTRADAHISTORIAL_H
#define ENTRADAHISTORIAL_H

#include <string>

class entradaHistorial {
 private:
    bool creado;
    bool modificado;
    bool borrado;
    std::size_t asientos;
    std::string origen;
    std::string destino;
    std::string oficina;
    std::string paisOficina;
    std::string continenteOficina;
    std::string owner;

 public:
    entradaHistorial();
    ~entradaHistorial();
    entradaHistorial(bool c, bool mo, bool bo, std::size_t as, std::string ori,
                     std::string des, std::string own, std::string of,
                     std::string paOf, std::string coOf);
    bool getCreado() const;
    void setCreado(bool value);
    bool getModificado() const;
    void setModificado(bool value);
    bool getBorrado() const;
    void setBorrado(bool value);
    std::size_t getAsientos() const;
    void setAsientos(std::size_t value);
    std::string getOrigen() const;
    void setOrigen(const std::string &value);
    std::string getDestino() const;
    void setDestino(const std::string &value);
    std::string getOficina() const;
    void setOficina(const std::string &value);
    std::string getPaisOficina() const;
    void setPaisOficina(const std::string &value);
    std::string getContinenteOficina() const;
    void setContinenteOficina(const std::string &value);
    std::string getOwner() const;
    void setOwner(const std::string &value);
};

#endif  // ENTRADAHISTORIAL_H
