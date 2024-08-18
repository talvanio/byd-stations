#include "../include/utils.hpp"
#include "../include/Naive.hpp"
#include "../include/Reformed.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

int main(int argc, char **argv)
{
    try
    {

        // Variáveis para armazenar os caminhos dos arquivos
        std::string stationsDataPath;
        std::string operationsDataPath;

        // Processa os argumentos da linha de comando
        if (argc != 5)
        {
            std::cerr << "Uso: " << argv[0] << " -b <arquivo de bases> -e <arquivo de eventos>" << std::endl;
            return 1;
        }

        // Processa os argumentos fornecidos
        for (int i = 1; i < argc; i += 2)
        {
            if (std::string(argv[i]) == "-b")
            {
                stationsDataPath = argv[i + 1];
            }
            else if (std::string(argv[i]) == "-e")
            {
                operationsDataPath = argv[i + 1];
            }
            else
            {
                std::cerr << "Argumento inválido: " << argv[i] << std::endl;
                return 1;
            }
        }

        // Abrindo o arquivo de estações:
        std::ifstream stationsDataFile(stationsDataPath);
        if (!stationsDataFile.is_open())
        {
            throw std::runtime_error ("Nao foi possivel abrir o arquivo indicado no caminho ");
        } 

        std::string numberOfStationsString;

        // Obtendo o numero de estacoes:
        std::getline(stationsDataFile, numberOfStationsString);
        int numberOfStations = std::stoi(numberOfStationsString);

        // Reformed biuaidi;
        Reformed biuaidireformed(numberOfStations);

        // Obtem as estacoes do arquivo e adiciona elas na QuadTree:
        biuaidireformed.getStationsFromFile(stationsDataFile);

        // Naive biuaidi
        // Naive naivebiuaidi;

        // Operações:

        char operation;
        int numberofOperations;
        std::string numberofOperationsString;

        // Abrindo o arquivo de operações:
        std::ifstream operationsDataFile(operationsDataPath);
        if (!operationsDataFile.is_open())
        {
            throw std::runtime_error ("Nao foi possivel abrir o arquivo indicado no caminho ");
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

                biuaidireformed.findKNearestNeighbors(kNearestNeighbours, originX, originY, k);

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
                std::cout << operation << " " << stationId << std::endl;

                // Printa o resultado:
                std::cout << biuaidireformed.deactivateById(stationId) << std::endl;
            }
            // Ativar estação:
            else if (operation == 'A')
            {
                // Recebe os dados da operação
                std::string stationId;
                std::cin >> stationId;

                // Printa a operação:
                std::cout << operation << " " << stationId << std::endl;

                // Printa o resultado:
                std::cout << biuaidireformed.activateById(stationId) << std::endl;
            }
            else
            {
                std::cerr << "Operacao não encontrada";
            }
        }

        // ptr_knn_t vetor_distancias = new knn_t[10];
        // biuaidireformed.findKNearestNeighbors(vetor_distancias, 613253.198013, 7804861.075791, 10);
        // for (int i = 0; i < 10; i++)
        // {
        //     vetor_distancias[i].print();
        // }
        return (0);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}