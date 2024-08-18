#include "../include/Station.hpp"
#include "../include/utils.hpp"

// Construtores:

Station::Station()
    : status('A'),address(""),x(0.0),y(0.0)
{
    status = 'A';
};
Station::Station(std::string _address, double _x, double _y)
    : status('A'),address(_address),x(_x),y(_y)

{
};

std::string Station::ativar()
{
    std::string res = "Ponto de recarga ";
    res.append(id);
    if(status == 'A')
    {
        res.append(" já estava ativo.");
    }
    else
    {
        status = 'A';
        res.append(" ativado.");
    }
    return res;
};

std::string Station::desativar()
{
    std::string res = "Ponto de recarga ";
    res.append(id);
    if(status == 'D')
    {
        res.append(" já estava desativado.");
    }
    else
    {
        status = 'D';
        res.append(" desativado.");
    }
    return res;
};

// Getters e Setters:
char Station::getStatus() const { return status; };
void Station::setStatus(char _status) { status = _status; };

std::string Station::getAddress() const { return address; };
void Station::setAddress(std::string _address) { address = _address; };

double Station::getX() const { return x; };
void Station::setX(double _x) { x = _x; };

double Station::getY() const { return y; };
void Station::setY(double _y) { y = _y; };

std::string Station::getId() const { return id; };
void Station::setId(std::string _id) { id = _id; };
