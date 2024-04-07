#ifndef LINES_H
#define LINES_H

#include <QPainter>

#include "Point.h"

class Lines {
public:
    static void dda(QPainter &painter, const Point &begin, const Point &end);
    static void bresenham_real(QPainter &painter, const Point &begin, const Point &end);
    static void bresenham_int(QPainter &painter, const Point &begin, const Point &end);
    static void bresenham_smooth(QPainter &painter, const Point &begin, const Point &end);
    static void wu(QPainter &painter, const Point &begin, const Point &end);
    static void library(QPainter &painter, const Point &begin, const Point &end);
};


#endif //LINES_H
