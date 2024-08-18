#include "../include/Reformed.hpp"
#include "utils.hpp"
#include <fstream>
#include <sstream>

Reformed::Reformed(int numberOfStations)
    : stations(numberOfStations),numberOfStations(numberOfStations),stationsHashTable(numberOfStations)
{
}

std::string Reformed::activateById(std::string stationId)
{
    return stationsHashTable.ativar(stationId);
}

std::string Reformed::deactivateById(std::string stationId)
{
    return stationsHashTable.desativar(stationId);
}


void Reformed::getStationsFromFile(std::ifstream &stationsDataFile)
{
    std::string rawAdress;
    std::string addressData[10];

    // Lê as linhas, transforma elas em stream para pegar os atributos das estações:
    for (int i = 0; i < numberOfStations; i++)
    {
        Station tempStation;

        std::getline(stationsDataFile, rawAdress);
        std::istringstream rawAdressStream(rawAdress);

        for (int i = 0; i < 10; i++)
        {
            std::string temp;
            std::getline(rawAdressStream, temp, ';');
            addressData[i] = temp;
        }

        // Seta o atributo Id da estacao como o Id do endereço (este será o único atributo do endereço que será utilizado para lógicas)
        const std::string stationId = addressData[0];
        tempStation.setId(stationId);

        // Seta a parte extensa do endereço (Parte a ser printada no final). A função addressify já coloca o endereço no formato de print
        // requisitado pelo enunciado.
        std::string endereco = addressify(addressData[1], addressData[2], addressData[3],
                                          addressData[4], addressData[5], addressData[6], addressData[7]);
        tempStation.setAddress(endereco);

        // Converte as coordenadas para doubles e coloca no atributo correspondente da estação:
        tempStation.setX(atof(addressData[8].c_str()));
        tempStation.setY(atof(addressData[9].c_str()));
        tempStation.setStatus('A');
        stations.insert(tempStation);
        stationsHashTable.Inserir(stationId);
    }
};

void Reformed::printQuadTree()
{
    stations.print();
}
int Reformed::getNumberOfStations()
{
    return numberOfStations;
}
void Reformed::setNumberOfStations(int _numberOfStations)
{
    numberOfStations = _numberOfStations;
}

Reformed::~Reformed()
{}