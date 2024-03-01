#ifndef SCALE_H
#define SCALE_H

#include "point.h"

#include <QGraphicsScene>
#include <QGraphicsItem>

#define MARKS_COUNT 11

#define BORDER 50

class Scale
{
private:
    Point left_bottom;
    Point right_upper;

    QGraphicsLineItem *x_axis, *y_axis;
    QGraphicsLineItem *x_marks[MARKS_COUNT], *y_marks[MARKS_COUNT];
    QGraphicsTextItem *x_marks_text[MARKS_COUNT], *y_marks_text[MARKS_COUNT];

    bool is_empty();
    void init();

public:
    QGraphicsScene *scene;
    QGraphicsView *view;

    void set_params(std::pair<Point, Point> scope);
    void clear();
    void draw();

    Scale();
};

#endif // SCALE_H
