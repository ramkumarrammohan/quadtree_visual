#include "quadtree.h"
#include <iostream>
#include <QPainter>

Quadtree::Quadtree(Boundary *boundary)
{
    m_boundary = boundary;
}

Quadtree::~Quadtree()
{
    for (size_t i = 0; i < m_points.size(); i++)
    {
        delete m_points[i];
    }
    m_points.clear();
    delete m_boundary;
    if (topleft)
        delete topleft;
    if (topright)
        delete topright;
    if (bottomleft)
        delete bottomleft;
    if (bottomright)
        delete bottomright;
}

bool Quadtree::insert(Point *point)
{
    if (!m_boundary->contains(point))
    {
        return false;
    }

    if (m_points.size() < m_capacity)
    {
        m_points.push_back(point);
        return true;
    } else
    {
        if (!divided)
        {
            subDivide();
        }
        if (topleft->insert(point))
            return true;

        if (topright->insert(point))
            return true;

        if (bottomleft->insert(point))
            return true;

        if (bottomright->insert(point))
            return true;
    }
    return false;
}

void Quadtree::query(Boundary *range, std::vector<Point*> *found)
{
    if (!this->m_boundary->intersects(range))
    {
        return;
    } else
    {
        foreach (Point *p, m_points)
        {
            if (range->contains(p))
            {
                found->push_back(p);
            }
        }

        if (this->divided)
        {
            this->topleft->query(range, found);
            this->topright->query(range, found);
            this->bottomleft->query(range, found);
            this->bottomright->query(range, found);
        }
    }
}

void Quadtree::show(QPainter *painter)
{
    QPen pen;
    pen.setColor(Qt::black);
    if (painter)
    {
        painter->drawRect(QRect(m_boundary->m_x - m_boundary->m_w,
                                m_boundary->m_y - m_boundary->m_h,
                                m_boundary->m_w * 2,
                                m_boundary->m_h * 2));
        foreach (Point *p, m_points) {
            painter->setPen(pen);
            painter->drawPoint(p->x(), p->y());
        }
        if (bottomright)
            bottomright->show(painter);
        if (topleft)
            topleft->show(painter);
        if (topright)
            topright->show(painter);
        if (bottomleft)
            bottomleft->show(painter);
    }
}

void Quadtree::subDivide()
{
    // Dividing boundaries
    Boundary *topleftBound = new Boundary(m_boundary->m_x - m_boundary->m_w / 2,
                                          m_boundary->m_y - m_boundary->m_h / 2,
                                          m_boundary->m_w / 2,
                                          m_boundary->m_h / 2);
    Boundary *toprightBound = new Boundary(m_boundary->m_x + m_boundary->m_w / 2,
                                           m_boundary->m_y - m_boundary->m_h / 2,
                                           m_boundary->m_w / 2,
                                           m_boundary->m_h / 2);
    Boundary *bottomleftBound = new Boundary(m_boundary->m_x - m_boundary->m_w / 2,
                                             m_boundary->m_y + m_boundary->m_h / 2,
                                             m_boundary->m_w / 2,
                                             m_boundary->m_h / 2);
    Boundary *bottomrightBound = new Boundary(m_boundary->m_x + m_boundary->m_w / 2,
                                              m_boundary->m_y + m_boundary->m_h / 2,
                                              m_boundary->m_w / 2,
                                              m_boundary->m_h / 2);

    topleft = new Quadtree(topleftBound);
    topright = new Quadtree(toprightBound);
    bottomleft = new Quadtree(bottomleftBound);
    bottomright = new Quadtree(bottomrightBound);
    divided = true;
}

bool Boundary::contains(Point *point)
{
    return (point->x() >= m_x - m_w &&
            point->x() <= m_x + m_w &&
            point->y() >= m_y - m_h &&
            point->y() <= m_y + m_h);
}

bool Boundary::intersects(const Boundary *range)
{
    return !(range->m_x - range->m_w > this->m_x + this->m_w ||
             range->m_x + this->m_w < this->m_x - this->m_w ||
             range->m_y - range->m_h > this->m_y + this->m_h ||
             range->m_y + this->m_h < this->m_y - this->m_h);
}
