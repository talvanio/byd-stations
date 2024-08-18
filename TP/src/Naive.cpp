#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include <sstream>
#include "../include/utils.hpp"
#include "../include/Naive.hpp"

// void Naive::printmap(ptr_knn_t distancesVector, int kmax, int numberOfStations, double originX, double originY)
// {
//   FILE *out;

//   // gnuplot script. to obtain the actual map, it is necessary to run:
//   // gnuplot out.gp
//   out = fopen("out.gp", "wt");
//   fprintf(out, "set term postscript eps\n");
//   fprintf(out, "set output \"out.eps\"\n");
//   fprintf(out, "set size square\n");
//   fprintf(out, "set key bottom right\n");
//   fprintf(out, "set title \"BiUaiDi Recharging Stations\"\n");
//   fprintf(out, "set xlabel \"\"\n");
//   fprintf(out, "set ylabel \"\"\n");
//   fprintf(out, "unset xtics \n");
//   fprintf(out, "unset ytics \n");
//   fprintf(out, "plot \"origin.gpdat\" t \"Your locatio\" pt 4 ps 2, \"recharge.gpdat\" t \"\", \"suggested.gpdat\" t \"Nearest stations\" pt 7 ps 2\n");
//   fclose(out);

//   out = fopen("origin.gpdat", "wt");
//   fprintf(out, "%f %f\n", originX, originY);
//   fclose(out);

//   // all recharging locations
//   out = fopen("recharge.gpdat", "wt");
//   for (int i = 0; i < numberOfStations; i++)
//   {
//     fprintf(out, "%f %f\n", estacoes[i].getX(), estacoes[i].getY());
//   }
//   fclose(out);

//   // the nearest recharging locations
//   out = fopen("suggested.gpdat", "wt");
//   for (int i = 0; i < kmax; i++)
//   {
//     fprintf(out, "%f %f\n", distancesVector[i].destiny.getX(), distancesVector[i].destiny.getY());
//   }
//   fclose(out);
// }

Naive::Naive()
{
}

void Naive::findKNearestNeighbors(ptr_knn_t res, double originX, double originY, int kmax)
{
  ptr_knn_t distancesVector = new knn_t[numberOfStations];

  for (int i = 0; i < numberOfStations; i++)
  {
    distancesVector[i].destiny = stations[i];
    distancesVector[i].dist = dist(originX, originY, stations[i].getX(), stations[i].getY());
  }

  // sort the vector of distances
  qsort(distancesVector, numberOfStations, sizeof(knn_t), compareKnn);

  int i = 0;
  int j = 0;

  while (i < numberOfStations && j < kmax)
  {
    if (distancesVector[i].destiny.getStatus() == 'A')
    {
      if (j >= kmax)
      {
        std::cerr << "Erro: Índice 'j' fora do limite do array res." << std::endl;
        break;
      }
      res[j] = distancesVector[i];
      j++;
    }
    i++;
  }

  return;
}

void Naive::getStationsFromFile(std::ifstream &stationsDataFile)
{
  std::string numberOfStationsString;

  // Obtendo o numero de estacoes:
  std::getline(stationsDataFile, numberOfStationsString);
  numberOfStations = std::stoi(numberOfStationsString);

  Station *stations = new Station[numberOfStations + 1];
  this->stations = stations;

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
    stations[i].setId(addressData[0]);

    // Seta a parte extensa do endereço (Parte a ser printada no final). A função addressify já coloca o endereço no formato de print
    // requisitado pelo enunciado.
    std::string endereco = addressify(addressData[1], addressData[2], addressData[3],
                                      addressData[4], addressData[5], addressData[6], addressData[7]);
    stations[i].setAddress(endereco);

    // Converte as coordenadas para doubles e coloca no atributo correspondente da estação:
    stations[i].setX(atof(addressData[8].c_str()));
    stations[i].setY(atof(addressData[9].c_str()));
    stations[i].setStatus('A');
  }
  stations[numberOfStations].setAddress("");
  stations[numberOfStations].setId("-1");
  stations[numberOfStations].setX(-1);
  stations[numberOfStations].setY(-1);
  stations[numberOfStations].setStatus('A');
};

std::string Naive::activateById(std::string id)
{
  for (int i = 0; i < numberOfStations; i++)
  {
    if (stations[i].getId() == id)
      return stations[i].ativar();
  }
  return "Estacao nao encontrada";
}
std::string Naive::deactivateById(std::string id)
{
  for (int i = 0; i < numberOfStations; i++)
  {
    if (stations[i].getId() == id)
      return stations[i].desativar();
  }
  return "Estacao nao encontrada";
}

Station *Naive::getStations()
{
  return stations;
};

int Naive::getNumberOfStations() 
{
  return numberOfStations;
}