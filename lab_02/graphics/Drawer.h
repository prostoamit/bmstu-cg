#ifndef DRAWER_H
#define DRAWER_H

#include "QPainter"

#include "DrawableFigure.h"
#include "FigureContainer.h"

/**
 *  @brief Class for drawing figures and figure containers on a QPainter.
 */
class Drawer {
public:
    /**
     * @brief Draws \p figure on a \p painter
     * @param painter
     * @param figure
     */
    static void draw_figure(QPainter &painter, size_t height, size_t width, DrawableFigure *figure);

    /**
     * Draws \p container on a \p painter
     * @param painter
     * @param container
     */
    static void draw_figure(QPainter &painter, size_t height, size_t width, FigureContainer *container);
};


#endif //DRAWER_H
