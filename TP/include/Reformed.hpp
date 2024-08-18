#ifndef REFORMED_HPP
#define REFORMED_HPP
#include "QuadTree.hpp"
#include "Set.hpp"
#include "utils.hpp"
class Reformed
{
public:
    Reformed(int quadTreeSize);
    ~Reformed();
    void getStationsFromFile(std::ifstream &stationsDataFile);
    std::string activateById(std::string stationId);
    std::string deactivateById(std::string stationId);
    void findKNearestNeighbors(ptr_knn_t res, double originX, double originY, int kmax);

    void printQuadTree();
    int getNumberOfStations();
    void setNumberOfStations(int _numberOfStations);


private:
    QuadTree stations;
    int numberOfStations;
    StringSet stationsHashTable;
};

#endif