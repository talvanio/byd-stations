#ifndef QUADTREE_HPP
#define QUADTREE_HPP
#include "../include/QuadTree.hpp"
#include "../include/Station.hpp"

class Node 
{
    public:
        Node();
        ~Node();
        Node(int capacity);
        // Node(int capacity,Rect boundary);
        Node(double _x,double _y);
        bool insertStation(Station station);

        double x,y;
        Station data;
        int nw,ne,sw,se = -1;
        bool isOcuppied = false;
};

class QuadTree 
{
    public:
        QuadTree(int quadTreeCapacity);
        ~QuadTree();
        void insert(const Station& station);
        bool insertInNode(int nodeIndex, Station station);
        bool subDivide(int nodeIndex);
        
        void print();

        void setCapacity(int _capacity);
        int getCapacity();
        Node getNode(int nodeIndex);

    private:
        Node* qtnodes;
        int size;
        int capacity;


};

#endif