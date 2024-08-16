#ifndef QUADTREE_HPP
#define QUADTREE_HPP

class Point
{
    public:
        Point(int _x,int _y);
        int getX();
        int getY();
        void setX(int _x);
        void setY(int _y);

    private:
        int x;
        int y;
};


struct Node 
{
    Rect boundary;
    Station* data;
    int nw,ne,sw,se = -1;
    bool isDivided = false;
    int size = 0;
};


struct Rect 
{
    public:
        float x,y,width,height;
        bool contains(float x, float y);
        bool intersects(const Rect& r);

};

class QuadTree 
{
    public:
        QuadTree(const Rect& boundary, int capacity);
        void insert(const Station& station);
        bool insertInNode(int nodeIndex, Station station);
        bool subDivide(int nodeIndex);

    private:
        Rect boundary;
        int capacity;
        Node* qtnodes;


};

#endif