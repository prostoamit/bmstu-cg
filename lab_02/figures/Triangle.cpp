#include "Triangle.h"

/**
 * @brief Create triangle
 * @param vertex_1
 * @param vertex_2
 * @param vertex_3
 */
Triangle::Triangle(Point vertex_1, Point vertex_2, Point vertex_3) {
    vertices.clear();

    vertices.push_back(vertex_1);
    vertices.push_back(vertex_2);
    vertices.push_back(vertex_3);
}
