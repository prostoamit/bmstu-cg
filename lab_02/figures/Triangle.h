#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "DrawableFigure.h"

class Triangle : virtual public DrawableFigure {
public:
    /**
     * @brief Saves 3 points that describe a triangle
     * @param vertex_1
     * @param vertex_2
     * @param vertex_3
     */
    Triangle(Point vertex_1, Point vertex_2, Point vertex_3);
};

#endif //TRIANGLE_H
