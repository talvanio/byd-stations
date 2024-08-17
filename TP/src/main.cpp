#include "../include/utils.hpp"
#include "../include/Naive.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

int main(int argc, char **argv)
{
    Naive naivebiuaidi;
    // Reformed reformedbiuaidi;

    // Leitura do arquivo de estações:
    std::string stationsDataPath = "../dados/geracarga.base";

    // Abrindo o arquivo de estações:
    std::ifstream stationsDataFile(stationsDataPath);
    if (!stationsDataFile.is_open())
    {
        std::cerr << "Nao foi possivel abrir o arquivo indicado no caminho " << stationsDataPath;
        return 1;
    }

    naivebiuaidi.getStationsFromFile(stationsDataFile);

    // Arquivo de operações:
    char operation;

    std::string operationsDataPath = "../dados/geracarga.ev";
    int numberofOperations;
    std::string numberofOperationsString;

    // Abrindo o arquivo de operações:
    std::ifstream operationsDataFile(operationsDataPath);
    if (!operationsDataFile.is_open())
    {
        std::cerr << "Nao foi possivel abrir o arquivo indicado no caminho " << operationsDataPath;
        return 1;
    }
    std::getline(operationsDataFile, numberofOperationsString);
    numberofOperations = std::stoi(numberofOperationsString) + 1;
    std::cin.rdbuf(operationsDataFile.rdbuf());

    // Operações:
    for (int i = 0; i < numberofOperations; i++)
    {
        std::cin >> operation;
        // Calcular k vizinhos + proximos:
        if (operation == 'C')
        {
            // Inicializa e recebe os dados da operação
            double originX, originY;
            int k;

            std::cin >> originX >> originY >> k;
            ptr_knn_t kNearestNeighbours = new knn_t[k];

            // calculateDistances(knn, stations, originX, originY, k, naive ou notNaive);

            naivebiuaidi.calculateDistances(kNearestNeighbours, originX, originY, k);


            std::cout << std::fixed << std::setprecision(6);
            // Printa a operação:
            std::cout << operation << " " << originX << " " << originY << " " << k << std::endl;

            // Printa o resultado:
            for (int i = 0; i < k; i++)
                kNearestNeighbours[i].print();
            delete[] kNearestNeighbours;
        }
        // Desativar estação:
        else if (operation == 'D')
        {
            // Recebe os dados da operação
            std::string stationId;
            std::cin >> stationId;
            // Printa a operação:
            std::cout << operation << " " << stationId<<std::endl;

            // Printa o resultado:
            std::cout << naivebiuaidi.deactivateById(stationId) << std::endl;
        }
        // Ativar estação:
        else if (operation == 'A')
        {
            // Recebe os dados da operação
            std::string stationId;
            std::cin >> stationId;

            // Printa a operação:
            std::cout << operation << " " << stationId<<std::endl;

            // Printa o resultado:
            std::cout << naivebiuaidi.activateById(stationId) << std::endl;
        }
        else
        {
            std::cerr << "Operacao não encontrada";
        }
    }

    return (0);
}