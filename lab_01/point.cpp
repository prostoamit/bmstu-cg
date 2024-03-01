#include "point.h"

#include <cmath>

bool
points_is_eq(Point l, Point r)
{
    double x_diff = l.x - r.x;
    double y_diff = l.y - r.y;

    return x_diff + y_diff < EPS;
}

void
point_copy(Point &dst, Point src)
{
    dst.x = src.x;
    dst.y = src.y;
}

double
distance_points(Point p1, Point p2)
{
    return sqrt((p1.x - p2.x) * (p1.x - p2.x) + (p1.y - p2.y) * (p1.y - p2.y));
}
