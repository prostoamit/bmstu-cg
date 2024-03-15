#include "triangle.h"

#include <cmath>

GraphicsTriangle::GraphicsTriangle()
{
    for (auto i : this->nodes)
        std::get<0>(i) = {0.0, 0.0};
}

GraphicsTriangle::GraphicsTriangle(Point p1, Point p2, Point p3)
{
    std::get<0>(this->nodes[0]) = p1;
    std::get<0>(this->nodes[1]) = p2;
    std::get<0>(this->nodes[2]) = p3;
}


bool
GraphicsTriangle::is_correct()
{
    double edges[] = {
        distance_points(std::get<0>(this->nodes[1]), std::get<0>(this->nodes[2])),
        distance_points(std::get<0>(this->nodes[2]), std::get<0>(this->nodes[0])),
        distance_points(std::get<0>(this->nodes[0]), std::get<0>(this->nodes[1]))
    };

    return true;
}

double
GraphicsTriangle::area()
{
    double edge_1 = distance_points(std::get<0>(this->nodes[1]), std::get<0>(this->nodes[2]));
    double edge_2 = distance_points(std::get<0>(this->nodes[2]), std::get<0>(this->nodes[0]));
    double edge_3 = distance_points(std::get<0>(this->nodes[0]), std::get<0>(this->nodes[1]));

    double semi_perimeter = 0.5 * (edge_1 + edge_2 + edge_3);
    return std::sqrt(semi_perimeter * (semi_perimeter - edge_1)* (semi_perimeter - edge_2)* (semi_perimeter - edge_3));
}

GraphicsCircle
GraphicsTriangle::circumcirle()
{
    double x1 = std::get<0>(this->nodes[0]).x;
    double y1 = std::get<0>(this->nodes[0]).y;
    double x2 = std::get<0>(this->nodes[1]).x;
    double y2 = std::get<0>(this->nodes[1]).y;
    double x3 = std::get<0>(this->nodes[2]).x;
    double y3 = std::get<0>(this->nodes[2]).y;


    double zx = (y1 - y2) * (x3 * x3 + y3 * y3) +
                (y2 - y3) * (x1 * x1 + y1 * y1) +
                (y3 - y1) * (x2 * x2 + y2 * y2);

    double zy = (x1 - x2) * (x3 * x3 + y3 * y3) +
                (x2 - x3) * (x1 * x1 + y1 * y1) +
                (x3 - x1) * (x2 * x2 + y2 * y2);

    double z = (x1 - x2) * (y3 - y1) - (y1 - y2) * (x3 - x1);

    double x_centre = -0.5 * zx / z;
    double y_centre = 0.5 * zy / z;

    double radius = distance_points({x1, y1}, {x_centre, y_centre});

    return GraphicsCircle({x_centre, y_centre}, radius);
}

double
GraphicsTriangle::circumcircle_area_diff()
{
    return this->circumcirle().area() - this->area();
}


std::pair<Point, Point>
GraphicsTriangle::scope()
{
    double x_min = std::get<0>(this->nodes[0]).x, y_min = std::get<0>(this->nodes[0]).y;
    double x_max = x_min, y_max = y_min;

    for (std::size_t i = 1; i < 3; i++)
    {
        if (std::get<0>(this->nodes[i]).x < x_min)
            x_min = std::get<0>(this->nodes[i]).x;
        if (std::get<0>(this->nodes[i]).y < y_min)
            y_min = std::get<0>(this->nodes[i]).y;
        if (std::get<0>(this->nodes[i]).x > x_max)
            x_max = std::get<0>(this->nodes[i]).x;
        if (std::get<0>(this->nodes[i]).y > y_max)
            y_max = std::get<0>(this->nodes[i]).y;
    }

    return std::pair<Point, Point>({x_min, y_min}, {x_max, y_max});
}
