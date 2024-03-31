#ifndef ELLIPSE_H
#define ELLIPSE_H

#include "DrawableFigure.h"

class Ellipse : virtual public DrawableFigure {
public:
    /**
     * @brief Generates MAX_POINTS_COUNT points, that describe an ellipse
     * @param center The center of the ellipse
     * @param a The length of ellipse minor axis
     * @param b The length of ellipses major axis
     */
    Ellipse(const Point &center, double a, double b);
};


#endif //ELLIPSE_H
