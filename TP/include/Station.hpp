#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>



class Station {
public:
    Station(std::string _address,double _x, double _y);

    void ativar();
    void desativar();

    char getStatus();
    std::string getAddress();
    double getX();
    double getY();

    void setStatus(char _status);
    void setAddress(std::string _address);

    void setX(double _x);
    void setY(double _y);

private:
    char status;
    std::string address;
    double x;
    double y;

};



