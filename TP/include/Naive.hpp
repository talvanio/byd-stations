#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <fstream>
#include "Station.hpp"

#ifndef NAIVE_HPP
#define NAIVE_HPP

class Naive {

public:
  Naive();

  void printmap(ptr_knn_t kvet, int kmax, int numberOfStations, double originX, double originY);

  // qsort comparison function between distances to recharging locations
  void findKNearestNeighbors(ptr_knn_t res, double originX, double originY, int kmax);

  void getStationsFromFile(std::ifstream &stationsDataFile);

  std::string activateById(std::string id);
  std::string deactivateById(std::string id);


  Station* getStations();
  int getNumberOfStations();
private:
  Station* stations;
  int numberOfStations;
};

  	

#endif