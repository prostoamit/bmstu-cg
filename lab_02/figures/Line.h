#ifndef LINE_H
#define LINE_H

#include "DrawableFigure.h"


class Line : virtual public DrawableFigure {
public:
    /**
     * @brief Saves 2 points, that describe a line segment.
     * @param point_1
     * @param point_2
     */
    Line(const Point &point_1, const Point &point_2);
};


#endif //LINE_H
