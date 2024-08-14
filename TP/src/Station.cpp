#include "../include/Station.hpp"
#include "utils.cpp"

class Station {
public:
    // Construtor:
    Station(std::string _adress,double _x, double _y) 
    {
        status = 'A';
        adress = _adress;
        x = _x;
        y = _y;
    };


    std::string ativar() {
        status = 'A';
    };

    std::string desativar() {
        status = 'D';
    };


    // Getters:
    char getStatus() { return status; };
    std::string getAdress() { return adress; };
    double getX() { return x; };
    double getY() { return y; };

    // Setters:
    void setStatus(char _status) { status = _status; };
    void setAdress(std::string _adress) { adress = _adress; };
    void setX(double _x) { x = _x; };
    void setY(double _y) { y = _y; };

private:
    char status;
    std::string adress;
    double x;
    double y;

};
