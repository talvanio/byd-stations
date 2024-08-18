#include <iostream>
#include <iomanip>

#include "../include/QuadTree.hpp"

Node::Node(double _x, double _y)
    : x(_x), y(_y), data(), nw(-1), ne(-1), sw(-1), se(-1), isOcuppied(false)
{
}

Node::Node()
    : x(0.0), y(0.0), data(), nw(-1), ne(-1), sw(-1), se(-1), isOcuppied(false)
{
}

Node::~Node()
{
}

bool Node::insertStation(Station station)
{
    try
    {
        data.setX(station.getX());
        data.setY(station.getY());
        data.setAddress(station.getAddress());
        data.setId(station.getId());
        isOcuppied = true;
        return true;
    }
    catch (const std::exception &e)
    {
        std::cerr << "Não foi possível inserir estação no nó" << '\n';
        return false;
    }
};
Node QuadTree::getNode(int nodeIndex)
{
    return qtnodes[nodeIndex];
};

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
    : size(1), capacity(quadTreeCapacity + 1)
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
        return true;
    }
    else
    {
        // Chama recursao pro noroeste:
        if (station.getX() < node.data.getX() && station.getY() > node.data.getY())
        {
            if (node.nw == -1) // Se o nó filho ainda não foi criado
            {
                node.nw = size++;
                qtnodes[node.nw] = Node(); // Inicializa o novo nó NE
            }
            return insertInNode(node.nw, station);
        }
        // Chama recursao pro nordeste:
        else if (station.getX() > node.data.getX() && station.getY() > node.data.getY())
        {
            if (node.ne == -1)
            {
                node.ne = size++;
                qtnodes[node.ne] = Node();
            }
            return insertInNode(node.ne, station);
        }
        // Chama recursao pro sudoeste:
        else if (station.getX() < node.data.getX() && station.getY() < node.data.getY())
        {
            if (node.sw == -1)
            {
                node.sw = size++;
                qtnodes[node.sw] = Node();
            }
            return insertInNode(node.sw, station);
        }
        // Chama recursao pro sudeste:
        else if (station.getX() > node.data.getX() && station.getY() < node.data.getY())
        {
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
            return false;
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