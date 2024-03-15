#include "solution.h"
#include "qgraphicsview.h"

#include <limits>

#define VIEW_BORDER 100

Solution::Solution()
{
}


std::pair<Point, Point>
Solution::scope()
{
    Point left_bottom = {
        std::get<0>(this->circle.centre).x - this->circle.radius,
        std::get<0>(this->circle.centre).y - this->circle.radius
    };

    Point right_upper = {
        std::get<0>(this->circle.centre).x + this->circle.radius,
        std::get<0>(this->circle.centre).y + this->circle.radius
    };

    return std::pair<Point, Point>(left_bottom, right_upper);
}

int
Solution::find(GraphicPoints &points)
{
    double min_diff = std::numeric_limits<double>::max();
    bool found = false;

    for (std::size_t i = 0; i < points.size(); i++)
        for (std::size_t j = i + 1; j < points.size(); j++)
            for (std::size_t k = j + 1; k < points.size(); k++)
            {
                GraphicsTriangle triangle(points.get_point(i), points.get_point(j), points.get_point(k));
                double current_diff = triangle.circumcircle_area_diff();

                if ((current_diff <= min_diff) && triangle.is_correct())
                {
                    this->triangle = triangle;
                    this->circle = triangle.circumcirle();
                    min_diff = current_diff;
                    found = 1;
                }
            }

    return !found;
}

int
Solution::draw(GraphicPoints &points)
{
    if (this->find(points) != 0)
        return 1;

    this->scene->clear();

    for (std::size_t i = 0; i < 3; i++)
    {
        std::get<1>(this->triangle.nodes[i]) = this->scene->addEllipse(1, 1, 1, 1);


        char buffer[256] = {0};
        std::snprintf(buffer, 255, "[%.1f, %.1f]", std::get<0>(this->triangle.nodes[i]).x, std::get<0>(this->triangle.nodes[i]).y);
        std::get<2>(this->triangle.nodes[i]) = this->scene->addText(buffer);
    }

    this->circumcircle = this->scene->addEllipse(1, 1, 1, 1);

    Point left_bottom = {
        std::get<0>(this->circle.centre).x - this->circle.radius,
        std::get<0>(this->circle.centre).y - this->circle.radius
    };

    Point right_upper = {
        std::get<0>(this->circle.centre).x + this->circle.radius,
        std::get<0>(this->circle.centre).y + this->circle.radius
    };

    this->scale.set_params(std::pair<Point, Point>(left_bottom, right_upper));
    this->scale.draw();

    double window_height = this->view->height();
    double window_width = this->view->width();

    double d = this->circle.radius * 2;

    double ratio = (std::min(window_height, window_width) - VIEW_BORDER * 2) / d;

    double ratio_x = ratio;
    double ratio_y = ratio;

    Point on_screen[3];

    for (std::size_t i = 0; i < 3; i++)
    {
        Point moved_to_left_bottom = {
            std::get<0>(this->triangle.nodes[i]).x - left_bottom.x,
            std::get<0>(this->triangle.nodes[i]).y - left_bottom.y
        };

        on_screen[i] = {
            moved_to_left_bottom.x * ratio_x + VIEW_BORDER - POINT_RAD_PIX * 0.5,
            window_height - moved_to_left_bottom.y * ratio_y - VIEW_BORDER - POINT_RAD_PIX * 0.5,
        };

        std::get<1>(this->triangle.nodes[i])->setRect(on_screen[i].x - POINT_RAD_PIX / 2, on_screen[i].y - POINT_RAD_PIX / 2, POINT_RAD_PIX, POINT_RAD_PIX);
        std::get<1>(this->triangle.nodes[i])->setBrush(Qt::black);

        std::get<2>(this->triangle.nodes[i])->setPos(on_screen[i].x, on_screen[i].y);
    }

    for (std::size_t i = 0; i < 3; i++)
        this->triangle_lines[i] = this->scene->addLine(
            on_screen[i].x, on_screen[i].y,
            on_screen[(i + 1) % 3].x, on_screen[(i + 1) % 3].y
            );

    Point circumcircle_moved_to_left_bottom = {
        std::get<0>(this->circle.centre).x - left_bottom.x,
        std::get<0>(this->circle.centre).y - left_bottom.y
    };

    Point circumcircle_on_screen = {
        circumcircle_moved_to_left_bottom.x * ratio_x + VIEW_BORDER - POINT_RAD_PIX * 0.5,
        window_height - circumcircle_moved_to_left_bottom.y * ratio_y - VIEW_BORDER - POINT_RAD_PIX * 0.5
    };

    double circumcircle_radius = distance_points(circumcircle_on_screen, on_screen[2]);

    this->circumcircle->setRect(
        circumcircle_on_screen.x - circumcircle_radius,
        circumcircle_on_screen.y - circumcircle_radius,
        circumcircle_radius * 2, circumcircle_radius * 2
        );

    this->text->setText("\nРешение - треугольник с вершинами в точках:\n\t1. x: " +
                        QString::fromStdString(std::to_string(std::get<0>(this->triangle.nodes[0]).x)) + "\ty: " + QString::fromStdString(std::to_string(std::get<0>(this->triangle.nodes[0]).y)) +
                        "\n\t2. x: " + QString::fromStdString(std::to_string(std::get<0>(this->triangle.nodes[1]).x)) + "\ty: " + QString::fromStdString(std::to_string(std::get<0>(this->triangle.nodes[1]).y)) +
                        "\n\t3. x: " + QString::fromStdString(std::to_string(std::get<0>(this->triangle.nodes[2]).x)) + "\ty: " + QString::fromStdString(std::to_string(std::get<0>(this->triangle.nodes[2]).y)) +
                        "\n\nПолощадь треугольника: " + QString::fromStdString(std::to_string(this->triangle.area())) + "\tПлощадь описанной окружности: " + QString::fromStdString(std::to_string(this->circle.area())) +
                        "\nИх разность: " + QString::fromStdString(std::to_string(this->triangle.circumcircle_area_diff())) + "\n" +
                        this->text->toPlainText()
                );

    return 0;
}
