#include "Point.h"

#include <math.h>

#define PI acos(-1.0)


Point::Point(const Point &other) {
    x = other.x;
    y = other.y;
}

inline double
to_rad(double angle) {
    return angle * (PI / 180.0);
}

void
Point::move(double dx, double dy) {
    this->x += dx;
    this->y += dy;
}

void
Point::rotate(const Point &center, double angle) {
    double r_cos = cos(to_rad(angle));
    double r_sin = sin(to_rad(angle));

    double x_tmp = x;

    x = (x - center.x) * r_cos + (y - center.y) * r_sin + center.x;
    y = -(x_tmp - center.x) * r_sin + (y - center.y) * r_cos + center.y;
}

void
Point::scale(const Point &center, double kx, double ky) {
    x = (x - center.x) * kx + center.x;
    y = (y - center.y) * ky + center.y;
}

void
Point::operator+= (const Point &right) {
    x += right.x;
    y += right.y;
}

void
Point::operator/= (double k) {
    x /= k;
    y /= k;
}
