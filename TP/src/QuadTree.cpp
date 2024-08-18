#include <iostream>
#include <iomanip>

#include "../include/QuadTree.hpp"

Rect::Rect() {};

Rect::Rect(double _x, double _y, double _width, double _height)
{
    x = _x;
    y = _y;
    width = _width;
    height = _height;
};

Node::Node(double _x, double _y)
    : x(_x), y(_y), nw(-1), ne(-1), sw(-1), se(-1), isOcuppied(false)
{
}

Node::Node()
    : x(0.0), y(0.0), nw(-1), ne(-1), sw(-1), se(-1), isOcuppied(false)
{
}

Node::~Node()
{
    
}

bool Node::insertStation(Station station)
{
    try
    {
        data = station;
        isOcuppied = true;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Não foi possível inserir estação no nó" << '\n';
        return false;
    }
};

bool Rect::contains(float x, float y)
{

    return x >= this->x - width && y >= this->y - height &&
           x <= this->x + width && y <= this->y + height;
}

bool Rect::intersects(const Rect &r)
{
    return !(r.x + r.width < x ||
             r.y + r.height < y ||
             r.x > x + width ||
             r.y > y + height);
}

void QuadTree::print()
{
    for (int i = 0; i < size; i++)
    {
        std::cout << qtnodes[i].data.getAddress() << std::endl;
    }
}
// @param boundary: X,Y,width e height do retangulo do rootNode
// @param capacity: capacidade maxima de cada Nó
QuadTree::QuadTree(int quadTreeCapacity)
    : capacity(quadTreeCapacity+1), size(1)
{
    qtnodes = new Node[capacity];
    for (int i = 0; i < capacity; i++)
    {
        qtnodes[i] = Node();
    }

    Node rootNode;
    rootNode.x = 0.0;
    rootNode.y = 0.0;
    rootNode.isOcuppied = true;
    qtnodes[0] = rootNode;
}

bool QuadTree::insertInNode(int nodeIndex, Station station)
{
    std::cout << std::fixed << std::setprecision(3);

    Node &node = qtnodes[nodeIndex];

    // Adiciona apenas em folhas (que nao tem filhos), que têm espaço livre ainda (Ou seja, node.size < capacity)
    if (!node.isOcuppied)
    {
        node.insertStation(station);
    }
    else
    {
        if (station.getX() < node.data.getX() && station.getY() > node.data.getY())
        {
            std::cout << "northWest" << std::endl;
            if (node.nw == -1) // Se o nó filho ainda não foi criado
            {
                node.nw = size++;
                qtnodes[node.nw] = Node(); // Inicializa o novo nó NE
            }
            return insertInNode(node.nw, station);
        }
        else if (station.getX() > node.data.getX() && station.getY() > node.data.getY())
        {
            std::cout << "northEast" << std::endl;

            if (node.ne == -1)
            {
                node.ne = size++;
                qtnodes[node.ne] = Node();
            }
            return insertInNode(node.ne, station);
        }
        else if (station.getX() < node.data.getX() && station.getY() < node.data.getY())
        {
            std::cout << "southWest" << std::endl;

            if (node.sw == -1)
            {
                node.sw = size++;
                qtnodes[node.sw] = Node();
            }
            return insertInNode(node.sw, station);
        }
        else if (station.getX() > node.data.getX() && station.getY() < node.data.getY())
        {
            std::cout << "southEast" << std::endl;

            if (node.se == -1)
            {
                node.se = size++;
                qtnodes[node.se] = Node();
            }
            return insertInNode(node.se, station);
        }
        else
        {
            std::cerr << "Erro, nao foi possivel encontrar coordenadas para o nó especificado." << std::endl;
        }
    }
}

void QuadTree::insert(const Station &station)
{

    insertInNode(0, station);
}

void QuadTree::setCapacity(int _capacity)
{
    capacity = _capacity;
}

int QuadTree::getCapacity()
{
    return capacity;
}

QuadTree::~QuadTree()
{
    delete[] qtnodes;
}