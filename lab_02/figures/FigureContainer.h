#ifndef FIGURECONTAINER_H
#define FIGURECONTAINER_H

#include <vector>

#include "BaseFigure.h"
#include "DrawableFigure.h"

/**
 * @brief Container class for figures
 */
class FigureContainer : virtual public DrawableFigure {
protected:
    std::vector<DrawableFigure *> figures;
public:
    FigureContainer();
    FigureContainer(const FigureContainer &other);
    FigureContainer& operator=(const FigureContainer &other);

    /**
     * @brief Moving all figures in a container by \p dx and \p dy
     * @param dx X delta
     * @param dy Y delta
     */
    void move(double dx, double dy) override;

    /**
     * @brief Rotating all figures in the container around the point \p center by the angle \p angle
     * @param center Rotating center
     * @param angle Rotating angle
     */
    void rotate(const Point &center, double angle) override;

    /**
     * @brief Scaling all figures in the container relatively to the point \p center by coefficients \p kx \p ky
     * @param center Scaling center
     * @param kx X scaling coefficient
     * @param ky Y scaling coefficient
     */
    void scale(const Point &center, double kx, double ky) override;

    /**
     * @brief Adding figure to the container
     * @param figure
     */
    void add(DrawableFigure *figure);

    /**
     * @brief Deleting figure from the container
     * @param figure
     */
    void remove(DrawableFigure *figure);

    /**
     * @brief Deletes all figures from the container
     */
    void clear();

    /**
     * @brief Calculates the center point of the container
     * @return Center point.
     */
    Point center() override;

    friend class Drawer;
};

#endif //FIGURECONTAINER_H
