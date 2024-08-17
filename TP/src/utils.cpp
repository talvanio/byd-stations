#include "../include/utils.hpp"
#include "../include/Station.hpp"
#include <sstream>
#include <fstream>
#include <math.h>
#include <iomanip>


// Funcao que converte o formato dos endereços recebidos para uma string simples que representa o endereço da forma que ele deve
// ser retornado ao usuário, para simplificar a classe stations e a redabilidade do codigo em geral
std::string addressify(std::string id_logrado,
                       std::string sigla_tipo, std::string nome_logra,
                       std::string numero_imo, std::string nome_bairr,
                       std::string nome_regio, std::string cep)
{
    std::string address = std::string();
    address.append(sigla_tipo);
    address.append(" ");
    address.append(nome_logra);
    address.append(", ");
    address.append(numero_imo);
    address.append(", ");
    address.append(nome_bairr);
    address.append(", ");
    address.append(nome_regio);
    address.append(", ");
    address.append(cep);
    return address;
};

void getStationsFromFile(Station *estacoes, std::ifstream &stationsDataFile, int numberOfStations)
{
    std::string numberOfStationsString;
    std::string rawAdress;
    std::string addressData[10];

    // Lê as linhas, transforma elas em stream para pegar os atributos das estações:
    for (int i = 0; i < numberOfStations; i++)
    {
        std::getline(stationsDataFile, rawAdress);
        std::istringstream rawAdressStream(rawAdress);

        for (int i = 0; i < 10; i++)
        {
            std::string temp;
            std::getline(rawAdressStream, temp, ';');
            addressData[i] = temp;
        }
        // Seta o atributo Id da estacao como o Id do endereço (este será o único atributo do endereço que será utilizado para lógicas)
        estacoes[i].setId(addressData[0]);

        // Seta a parte extensa do endereço (Parte a ser printada no final). A função addressify já coloca o endereço no formato de print
        // requisitado pelo enunciado.
        std::string endereco = addressify(addressData[1], addressData[2], addressData[3],
                                          addressData[4], addressData[5], addressData[6], addressData[7]);
        estacoes[i].setAddress(endereco);

        // Converte as coordenadas para doubles e coloca no atributo correspondente da estação:
        estacoes[i].setX(atof(addressData[8].c_str()));
        estacoes[i].setY(atof(addressData[9].c_str()));
    }
    estacoes[numberOfStations].setAddress("");
    estacoes[numberOfStations].setId("-1");
    estacoes[numberOfStations].setX(-1);
    estacoes[numberOfStations].setY(-1);
};

// calculates Euclidean distance between (x1,y1) and (x2,y2)
double dist(double x1, double y1, double x2, double y2)
{
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}

// Compara 2 objetos knn
int compareKnn(const void *a, const void *b)
{
    ptr_knn_t k1 = (ptr_knn_t)a;
    ptr_knn_t k2 = (ptr_knn_t)b;
    if (k1->dist > k2->dist)
        return 1;
    else if (k1->dist < k2->dist)
        return -1;
    else
        return 0;
}

void knn::print()
{
    std::cout << std::fixed << std::setprecision(3);
    std::cout << this->destiny.getAddress();
    std::cout << " ";
    std::cout << "(" << this->dist << ")" << std::endl;
}