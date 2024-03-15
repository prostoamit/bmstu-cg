#include "circle.h"

#include <cmath>
#define PI acos(-1.0)

GraphicsCircle::GraphicsCircle()
{
    std::get<0>(this->centre) = {0.0, 0.0};
    this->radius = 0.0;
}

GraphicsCircle::GraphicsCircle(Point centre, double radius)
{
    std::get<0>(this->centre) = centre;
    this->radius = radius;
}

double GraphicsCircle::area()
{
    return PI * this->radius * this->radius;
}
