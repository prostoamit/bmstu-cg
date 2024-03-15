#ifndef POINTS_H
#define POINTS_H

#include "point.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

#include <vector>

#define POINT_RAD_PIX 5

class GraphicPoints
{
private:
    std::vector<std::tuple<Point, QGraphicsEllipseItem*, QGraphicsTextItem*>> points;

    Point left_bottom;
    Point right_upper;

public:
    QGraphicsScene *scene;
    QGraphicsView *view;

private:
    Point find_left_bottom();
    Point find_right_upper();

    void points_modify_for_scene();

public:
    GraphicPoints();

    void set_scene(QGraphicsScene* scene);

    Point get_point(std::size_t n);
    int edit_point(std::size_t n, Point point);

    std::size_t size();
    void push_back(Point point);
    int remove(std::size_t position);
    void clear();

    std::pair<Point, Point> scope();
};

#endif // POINTS_H
