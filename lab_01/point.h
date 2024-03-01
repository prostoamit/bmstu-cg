#ifndef POINT_H
#define POINT_H

#define EPS 1e-6

struct Point
{
    double x, y;
};

bool points_is_eq(Point l, Point r);

void point_copy(Point &dst, Point src);

double distance_points(Point p1, Point p2);

#endif // POINT_H
