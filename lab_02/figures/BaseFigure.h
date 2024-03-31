#ifndef BASEFIGURE_H
#define BASEFIGURE_H

#include <vector>

#include "Point.h"

/**
 * @brief Base class for figures. Provides interface, required for all figures
 */
class BaseFigure {
public:
    /**
     * @brief Moving the figure by \p dx and \p dy
     * @param dx X delta
     * @param dy Y delta
     */
    virtual void move(double dx, double dy) {}

    /**
     * @brief Rotating the figure around point \p center by the angle \p angle
     * @param center Rotating center
     * @param angle Rotating angle
     */
    virtual void rotate(const Point &center, double angle) {}

    /**
     * @brief Scaling the figure from point \p center by coefficients \p kx \p ky
     * @param center Scaling center
     * @param kx X scaling coefficient
     * @param ky Y scaling coefficient
     */
    virtual void scale(const Point &center, double kx, double ky) {}

    /**
    * @brief Calculates the center point of the figure.
    * @return Center point.
    */
    virtual Point center() = 0;
};

#endif //BASEFIGURE_H
