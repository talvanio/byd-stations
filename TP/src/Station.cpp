#include "../include/Station.hpp"
#include "utils.cpp"

class Station {
public:
    Station(char * idend, long id_logrado, char * sigla_tipo,char * nome_logra, int numero_imo, char * nome_bairr, char * nome_regio) 
    {
        idend = idend;
        id_logrado = id_logrado;
        sigla_tipo = sigla_tipo;
        nome_logra = nome_logra;
        numero_imo = numero_imo;
    }


    std::string ativar();
    std::string desativar();


    // Getters
    char getStatus() { return status; }
    char * getIdend() { return idend; }
    long getId_logrado() { return id_logrado; }
    char * getSigla_tipo() { return sigla_tipo; }
    char * getNome_logra() { return nome_logra; }
    int getNumero_imo() { return numero_imo; }
    char * getNome_bairr() { return nome_bairr; }
    int getCep() { return cep; }
    double getX() { return x; }
    double getY() { return y; }

    // Setters
    void setStatus(char _status) { status = _status; }
    void setIdend(char *_idend) { idend = _idend; }
    void setId_logrado(long _id_logrado) { id_logrado = _id_logrado; }
    void setSigla_tipo(char *_sigla_tipo) { sigla_tipo = _sigla_tipo; }
    void setNome_logra(char *_nome_logra) { nome_logra = _nome_logra; }
    void setNumero_imo(int _numero_imo) { numero_imo = _numero_imo; }
    void setNome_bairr(char *_nome_bairr) { nome_bairr = _nome_bairr; }
    void setCep(int _cep) { cep = _cep; }
    void setX(double _x) { x = _x; }
    void setY(double _y) { y = _y; }

private:
    char status;
    char * idend;
    long id_logrado;
    char * sigla_tipo;
    char * nome_logra;
    int numero_imo;
    char * nome_bairr;
    char * nome_regio;
    int cep;
    double x;
    double y;

};
