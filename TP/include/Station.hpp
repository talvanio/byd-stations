#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>



class Station {
public:
    Station(std::string _adress,double _x, double _y);

    std::string ativar();
    std::string desativar();

    char getStatus();
    char* getAdress();
    double getX();
    double getY();

    void setStatus(char _status);
    void setAdress(std::string _adress);

    void setX(double _x);
    void setY(double _y);

private:
    char status;
    std::string adress;
    double x;
    double y;

};



