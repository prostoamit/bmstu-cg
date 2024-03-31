#ifndef DRAWABLEFIGURE_H
#define DRAWABLEFIGURE_H

#include "BaseFigure.h"

#include <vector>

#include "Point.h"

#define MAX_POINTS_COUNT 1000

/**
 * @brief Figure class that contains a vector of figure's vertices
 *
 * All figure transformations are in fact transformations of all the points, contained in a vector.
 */
class DrawableFigure : virtual public BaseFigure {
protected:
    std::vector<Point> vertices;
public:
    DrawableFigure();
    DrawableFigure(const DrawableFigure &other);
    DrawableFigure& operator=(const DrawableFigure &other);

    virtual ~DrawableFigure() {};

    /**
     * @brief Moving the figure by \p dx and \p dy
     * @param dx X delta
     * @param dy Y delta
     */
    void move(double dx, double dy) override;

    /**
     * @brief Rotating the figure around point \p center by the angle \p angle
     * @param center Rotating center
     * @param angle Rotating angle
     */
    void rotate(const Point &center, double angle) override;

    /**
     * @brief Scaling the figure from point \p center by coefficients \p kx \p ky
     * @param center Scaling center
     * @param kx X scaling coefficient
     * @param ky Y scaling coefficient
     */
    void scale(const Point &center, double kx, double ky) override;

    /**
    * @brief Calculates the center point of the figure.
    * @return Center point.
    */
    Point center() override;

    friend class Drawer;
};


#endif //DRAWABLEFIGURE_H
