#include "../include/Station.hpp"
#include "utils.cpp"

// Construtor:
Station::Station(std::string _address,double _x, double _y) 
{
    status = 'A';
    address = _address;
    x = _x;
    y = _y;
};


void Station::ativar() 
{
    status = 'A';
};

void Station::desativar() {
    status = 'D';
};


// Getters e Setters:

// Status
char Station::getStatus() 
{ 
    return status; 
};
void Station::setStatus(char _status) 
{ 
    status = _status; 
};

// Address
std::string Station::getAddress() 
{ 
    return address; 
};
void Station::setAddress(std::string _address) 
{ 
    address = _address; 
};

//X
double Station::getX() 
{ 
    return x; 
};
void Station::setX(double _x) 
{ 
    x = _x; 
};

//Y
double Station::getY() 
{ 
    return y; 
};
void Station::setY(double _y) 
{ 
    y = _y; 
};
