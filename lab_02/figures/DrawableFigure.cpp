#include "DrawableFigure.h"


DrawableFigure::DrawableFigure() {}

DrawableFigure::DrawableFigure(const DrawableFigure &other) {
    vertices.reserve(other.vertices.size());

    vertices.clear();
    for (const Point &point : other.vertices)
        vertices.push_back(Point(point.get_x(), point.get_y()));
}

DrawableFigure&
DrawableFigure::operator=(const DrawableFigure &other) {
    if (this != &other) {
        vertices.clear();

        vertices.reserve(other.vertices.size());
        for (const Point &point : other.vertices)
            vertices.push_back(Point(point.get_x(), point.get_y()));
    }
    return *this;
}

void
DrawableFigure::move(double dx, double dy) {
    for (Point &i : vertices)
        i.move(dx, dy);
}

void
DrawableFigure::rotate(const Point &center, double angle) {
    for (Point &i : vertices)
        i.rotate(center, angle);
}

void
DrawableFigure::scale(const Point &center, double kx, double ky) {
    for (Point &i : vertices)
        i.scale(center, kx, ky);
}

Point
DrawableFigure::center() {
    Point center;

    for (Point &i : vertices)
        center += i;

    center /= double(vertices.size());

    return center;
}
