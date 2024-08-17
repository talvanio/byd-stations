#include "Station.hpp"
#include <string>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#ifndef UTILS_HPP
#define UTILS_HPP


// struct that contain the distance information between the origin location and
// each recharging location.
typedef struct knn
{
  double dist; // distance between origin location and recharging location
  Station destiny;
  void print();
} knn_t, *ptr_knn_t;


std::string addressify(std::string id_logrado, 
                     std::string sigla_tipo, std::string nome_logra,
                     std::string numero_imo,std::string nome_bairr,
                     std::string nome_regio,std::string cep);


void getStationsFromFile(Station* estacoes,std::ifstream& stationsDataFile, int numberOfStations);

double dist(double x1, double y1, double x2, double y2);
int compareKnn(const void *a, const void *b);

#endif