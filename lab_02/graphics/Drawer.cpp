#include "Drawer.h"

#include <QPainterPath>

#include <QPen>

void
Drawer::draw_figure(QPainter &painter, size_t height, size_t width, FigureContainer *container) {
    for (DrawableFigure *figure : container->figures)
        draw_figure(painter, height, width, figure);
}

void
Drawer::draw_figure(QPainter &painter, size_t height, size_t width, DrawableFigure *figure) {
    QPainterPath figure_path;

    QVector<QPointF> polygon_vertices;

    for (Point &i : figure->vertices)
        polygon_vertices.append(QPointF(width / 2 + i.get_x(), height / 2 - i.get_y()));
    polygon_vertices.append(QPointF(width / 2 + figure->vertices[0].get_x(), height / 2 - figure->vertices[0].get_y()));

    QPolygonF polygon(polygon_vertices);

    figure_path.addPolygon(polygon);
//    painter.setPen(QPen(Qt::black, 3));
    painter.drawPath(figure_path);
}
