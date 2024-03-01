#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "point.h"
#include "circle.h"

#include <utility>

#include <QGraphicsScene>
#include <QGraphicsItem>

class GraphicsTriangle
{
public:
    std::tuple<Point, QGraphicsEllipseItem*, QGraphicsTextItem*> nodes[3];

public:
    GraphicsTriangle();
    GraphicsTriangle(Point p1, Point p2, Point p3);

    double area();
    GraphicsCircle circumcirle();

    double circumcircle_area_diff();

    std::pair<Point, Point> scope();
};

#endif // TRIANGLE_H
