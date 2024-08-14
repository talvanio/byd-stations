#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string>



class Station {
public:
    Station(char * idend, long id_logrado,
            char * sigla_tipo,char * nome_logra, int numero_imo,
            char * nome_bairr, char * nome_regio);

    Station(int _idend);


    std::string ativar();
    std::string desativar();

    char getStatus();
    char* getAdress();
    double getX();
    double getY();

    void setStatus(char _status);
    void setAdress(char* _adress);
    void setAdress(char * idend, long id_logrado,
                    char * sigla_tipo,char * nome_logra, int numero_imo,
                    char * nome_bairr, char * nome_regio);

    void setX(double _x);
    void setY(double _y);





private:
    char status;
    char* adress;
    double x;
    double y;

};



