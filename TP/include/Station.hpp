#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>

#ifndef STATION_HPP
#define STATION_HPP

class Station {
public:
    //Construtores
    Station();
    Station(std::string _address,double _x, double _y);

    std::string ativar();
    std::string desativar();

    // Getters e setters:
    void setStatus(char _status);
    char getStatus();


    void setAddress(std::string _address);
    std::string getAddress();

    void setX(double _x);
    double getX();

    void setY(double _y);
    double getY();


    void setId(std::string _id);
    std::string getId();



private:
    std::string id;
    char status;
    std::string address;
    double x;
    double y;

};

#endif