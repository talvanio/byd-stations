#include "../include/QuadTree.hpp"
#include "../include/Station.hpp"




bool Rect::contains(float x, float y) 
{
    return x >= this->x && y >= this->y &&
           x <= this->x + width && y <= this->y + height;
}


bool Rect::intersects(const Rect& r)
{
    return !(r.x + r.width < x || 
                r.y + r.height < y ||
                r.x > x + width ||
                r.y > y + height);
}

// @param boundary: X,Y,width e height do retangulo do rootNode
// @param capacity: capacidade maxima de cada Nó
QuadTree::QuadTree(const Rect& boundary, int capacity)
    : capacity(capacity) 
{
    Node rootNode{boundary};
    qtnodes[0] = rootNode;
}

bool QuadTree::insertInNode(int nodeIndex, Station station)
{
    Node& node = qtnodes[nodeIndex];
    // Se não intercepta, essa estacao não é para ser inserida neste nó.
    if(!node.boundary.contains(station.getX(),station.getY()));
    {
        return false;
    }


    // Adiciona apenas em folhas (que nao tem filhos), que têm espaço livre ainda (Ou seja, node.size < capacity)
    if(!node.isDivided)
    {
        if(node.size < capacity)
        {
            node.data[node.size] = station;
            return true;
        }
        else
        {
            // Subidivide e tenta inserir novamente:
            subDivide(nodeIndex);
            return(insertInNode(nodeIndex,station));
        }
    } else {
        insertInNode(node.nw,station);
        insertInNode(node.ne,station);
        insertInNode(node.sw,station);
        insertInNode(node.se,station);
    }

}



void QuadTree::insert(const Station& station)
{
    insertInNode(0,station);
}


