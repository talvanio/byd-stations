#include "utils.cpp"
#include <fstream>
#include <iostream>
#include <sstream>

int main() 
{

    // Abrindo o arquivo de estações:
    std::string stationsDataPath = "../../dados/geracarga.base";
    std::ifstream stationsDataFile(stationsDataPath);
    std::string rawAdress;
    std::string adressData[10];

    if(!stationsDataFile.is_open()) 
    {
        std::cerr << "Nao foi possivel abrir o arquivo indicado no caminho " << stationsDataPath;
        return 1;
    }

    std::string numberOfStationsString;
    int numberOfStations;

    std::getline(stationsDataFile,numberOfStationsString);
    numberOfStations = std::stoi(numberOfStationsString);

    // Le as linhas, transforma elas em stream para pegar cada atributo de cada linha:
    for(int i=0;i<numberOfStations;i++) 
    {
        std::getline(stationsDataFile,rawAdress);
        std::istringstream rawAdressStream(rawAdress);

        for(int i=0;i<10;i++)
            {
                std::string temp;
                std::getline(rawAdressStream,temp,';');
                adressData[i] = temp;
            }
    
        std::string endereco = adressify(adressData[0],adressData[1],adressData[2],adressData[3],
                    adressData[4],adressData[5],adressData[6],adressData[7]);
        std::cout<<endereco<<std::endl;
    }

    return(0);
}