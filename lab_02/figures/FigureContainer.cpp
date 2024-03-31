#include "FigureContainer.h"

FigureContainer::FigureContainer() {}

FigureContainer::FigureContainer(const FigureContainer &other) : DrawableFigure(other) {
    figures.reserve(other.figures.size());
    for (const DrawableFigure *figure : other.figures) {
        DrawableFigure *newFigure = new DrawableFigure(*figure);
        figures.push_back(newFigure);
    }
}

FigureContainer&
FigureContainer::operator=(const FigureContainer &other) {
    if (this != &other) {
        clear();

        DrawableFigure::operator=(other);

        figures.reserve(other.figures.size());
        for (const DrawableFigure *figure : other.figures) {
            DrawableFigure *newFigure = new DrawableFigure(*figure);
            figures.push_back(newFigure);
        }
    }
    return *this;
}

void
FigureContainer::move(double dx, double dy) {
    for (BaseFigure *i : figures)
        i->move(dx, dy);
}

void
FigureContainer::rotate(const Point &center, double angle) {
    for (BaseFigure *i : figures)
        i->rotate(center, angle);
}

void
FigureContainer::scale(const Point &center, double kx, double ky) {
    for (BaseFigure *i : figures)
        i->scale(center, kx, ky);
}

void
FigureContainer::add(DrawableFigure *figure) {
    figures.push_back(figure);
}

void
FigureContainer::remove(DrawableFigure *figure) {
    return;
}

void
FigureContainer::clear() {
    figures.clear();
}

Point
FigureContainer::center() {
    Point center;

    for (DrawableFigure *i : figures)
        center += i->center();

    center /= figures.size();

    return center;
}
