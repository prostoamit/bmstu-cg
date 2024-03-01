#ifndef CIRCLE_H
#define CIRCLE_H

#include "point.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

class GraphicsCircle
{
public:
    std::tuple<Point, QGraphicsEllipseItem*, QGraphicsTextItem*> centre;
    double radius;

public:
    GraphicsCircle();
    GraphicsCircle(Point centre, double radius);

    double area();
};

#endif // CIRCLE_H
