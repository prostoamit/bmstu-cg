#include "Ellipse.h"

#include <cmath>

#define PI acos(-1.0)

Ellipse::Ellipse(const Point &center, double a, double b) {
    vertices.clear();

    double t = 0.0;
    double t_step = 2 * M_PI / MAX_POINTS_COUNT;

    for (int i = 0; i < MAX_POINTS_COUNT; i++, t += t_step)
        vertices.push_back(Point(a * cos(t) + center.get_x(), b * sin(t) + center.get_y()));
}
