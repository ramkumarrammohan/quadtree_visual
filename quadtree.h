#ifndef QUADTREE_H
#define QUADTREE_H

#include <vector>

class QPainter;
class Point
{
public:
    Point(int x, int y)
    {
        m_x = x;
        m_y = y;
    }
    int x()
    {
        return m_x;
    }
    int y()
    {
        return m_y;
    }

private:
    int m_x = 0;
    int m_y = 0;
};

class Boundary
{
public:
    Boundary(int x, int y, int w, int h)
    {
        m_x = x;    m_y = y;
        m_w = w;    m_h = h;
    }
    int m_x = 0, m_y = 0;
    int m_w = 0, m_h = 0;

    bool contains(Point *point);
    bool intersects(const Boundary *range);
};

class Quadtree
{
public:
    Quadtree(Boundary *boundary);
    ~Quadtree();
    bool insert(Point *point);
    void query(Boundary *range, std::vector<Point *> *found);
    void show(QPainter *painter);

private:
    bool divided = false;
    unsigned short m_capacity = 4;
    Boundary *m_boundary;
    std::vector<Point*> m_points;

    Quadtree *topleft = nullptr;
    Quadtree *topright = nullptr;
    Quadtree *bottomleft = nullptr;
    Quadtree *bottomright = nullptr;

    void subDivide();
};

#endif // QUADTREE_H
