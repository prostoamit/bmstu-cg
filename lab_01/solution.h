#ifndef SOLUTION_H
#define SOLUTION_H

#include "point.h"
#include "points.h"

#include "qtextbrowser.h"
#include "triangle.h"
#include "circle.h"
#include "scale.h"

#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QMainWindow>

class Solution
{
private:
    GraphicsCircle circle;
    GraphicsTriangle triangle;
    QGraphicsLineItem *triangle_lines[3];
    QGraphicsEllipseItem *circumcircle;

public:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QTextBrowser *text;

    Scale scale;

public:
    Solution();

    int draw(GraphicPoints &points);
    std::pair<Point, Point> scope();

private:
    int find(GraphicPoints &points);
};

#endif // SOLUTION_H
