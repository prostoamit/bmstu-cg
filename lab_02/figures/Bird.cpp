#include "Bird.h"

#include "Ellipse.h"
#include "Triangle.h"
#include "Line.h"

Bird::Bird() {
    this->add(new Ellipse(Point(0.0, 0.0), 10.0, 6.0));
    this->add(new Ellipse(Point(-7.4141225, 7.3838265), 3.0, 3.0));
    this->add(new Triangle(Point(-9.4141225, 7.3838265), Point(-14.0, 7.3838265), Point(-9.4141225, 9.61989)));
    this->add(new Triangle(Point(0.0, 0.0), Point(5.0, 0.0), Point(8.0, -7.0)));
    this->add(new Triangle(Point(8.0, 0.0), Point(8.0, -2.0), Point(12.0, -2.0)));
    this->add(new Line(Point(-4.0, -5.4990908), Point(-5.0, -10.0)));
    this->add(new Line(Point(0.0, -6.0), Point(1.0, -10.0)));

    Point center = this->center();

    this->move(-center.get_x() + 1e-5, -center.get_y() + 1e-5);
}

Bird::~Bird() {
    for (size_t i = 0; i < figures.size(); ++i)
        delete figures[i];

    figures.clear();
}


void
Bird::to_default() {
    *this = Bird();
}
