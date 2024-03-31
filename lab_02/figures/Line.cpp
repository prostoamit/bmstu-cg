#include "Line.h"


Line::Line(const Point &point_1, const Point &point_2) {
    vertices.clear();

    vertices.push_back(point_1);
    vertices.push_back(point_2);
}