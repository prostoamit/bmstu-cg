#include "points.h"
#include "qgraphicsview.h"

#define VIEW_BORDER 100

GraphicPoints::GraphicPoints()
{
    this->left_bottom = {0.0, 0.0};
    this->right_upper = {0.0, 0.0};
}

void
GraphicPoints::set_scene(QGraphicsScene* scene)
{
    this->scene = scene;
}

std::size_t
GraphicPoints::size()
{
    return this->points.size();
}

void
GraphicPoints::points_modify_for_scene()
{
    double window_height = this->view->height();
    double window_width = this->view->width();

    double d_x = right_upper.x - left_bottom.x;
    double d_y = right_upper.y - left_bottom.y;

    double d = d_x > d_y ? d_x : d_y;

    if (d < EPS)
    {
        for (size_t i = 0; i < this->size(); i++)
        {
            std::get<1>(this->points[i])->setRect(VIEW_BORDER - POINT_RAD_PIX * 0.5, this->view->height() - VIEW_BORDER - POINT_RAD_PIX * 0.5, POINT_RAD_PIX, POINT_RAD_PIX);
            std::get<1>(this->points[i])->setBrush(Qt::black);
            std::get<2>(this->points[i])->setPos(VIEW_BORDER, this->view->height() - VIEW_BORDER);
        }
        return;
    }

    double ratio_x = (window_width - VIEW_BORDER * 2) / d;
    double ratio_y = (window_height - VIEW_BORDER * 2) / d;

    for (auto i : this->points)
    {
        Point moved_to_left_bottom = {
            std::get<0>(i).x - this->left_bottom.x,
            std::get<0>(i).y - this->left_bottom.y
        };

        Point on_screen = {
            moved_to_left_bottom.x * ratio_x + VIEW_BORDER - POINT_RAD_PIX * 0.5,
            window_height - moved_to_left_bottom.y * ratio_y - VIEW_BORDER - POINT_RAD_PIX * 0.5,
        };

        std::get<1>(i)->setRect(on_screen.x, on_screen.y, POINT_RAD_PIX, POINT_RAD_PIX);
        std::get<2>(i)->setPos(on_screen.x, on_screen.y);
        std::get<1>(i)->setBrush(Qt::black);
    }

}

Point
GraphicPoints::get_point(std::size_t n)
{
    return std::get<0>(this->points[n]);
}

int
GraphicPoints::edit_point(std::size_t n, Point point)
{
    if (n >= this->points.size())
        return -1;

    remove(n);

    push_back(point);

    return 0;
}

void
GraphicPoints::push_back(Point point)
{
    QGraphicsEllipseItem *dot = this->scene->addEllipse(1, 1, 1, 1);
    char buffer[256] = {0};
    std::snprintf(buffer, 255, "[%.2lf, %.2lf]", point.x, point.y);
    QGraphicsTextItem *text = this->scene->addText(QString::fromStdString(buffer));
    this->points.push_back(std::tuple<Point, QGraphicsEllipseItem*, QGraphicsTextItem*>(point, dot, text));

    if (this->points.size() == 1)
    {
        point_copy(this->left_bottom, point);
        point_copy(this->right_upper, point);
    }
    else
    {
        if (point.x < this->left_bottom.x)
            this->left_bottom.x = point.x;
        if (point.y < this->left_bottom.y)
            this->left_bottom.y = point.y;
        if (point.x > this->right_upper.x)
            this->right_upper.x = point.x;
        if (point.y > this->right_upper.y)
            this->right_upper.y = point.y;
    }

    this->points_modify_for_scene();
}

int
GraphicPoints::remove(std::size_t position)
{
    if (this->points.size() <= position)
        return 1;

    this->scene->removeItem(std::get<1>(this->points[position]));
    this->scene->removeItem(std::get<2>(this->points[position]));
    this->points.erase(this->points.begin() + position);

    this->right_upper = this->find_right_upper();
    this->left_bottom = this->find_left_bottom();

    double c_x = this->left_bottom.x + (this->right_upper.x - this->left_bottom.x) / 2;
    double c_y = this->left_bottom.y + (this->right_upper.y - this->left_bottom.y) / 2;

    this->view->centerOn(c_x, c_y);
    this->points_modify_for_scene();

    return 0;
}

std::pair<Point, Point> GraphicPoints::scope()
{
    return std::pair<Point, Point>(this->left_bottom, this->right_upper);
}

void
GraphicPoints::clear()
{
    this->scene->clear();
    this->points.clear();

    this->left_bottom = {0.0, 0.0};
    this->right_upper = {0.0, 0.0};
}

Point
GraphicPoints::find_left_bottom()
{
    if (this->points.size() == 0)
        return {0.0, 0.0};

    Point left_bottom = {std::get<0>(this->points[0]).x, std::get<0>(this->points[0]).y};

    for (std::size_t i = 0; i < this->points.size(); i++)
    {
        if (std::get<0>(this->points[i]).x < left_bottom.x)
            left_bottom.x = std::get<0>(this->points[i]).x;

        if (std::get<0>(this->points[i]).y < left_bottom.y)
            left_bottom.y = std::get<0>(this->points[i]).y;
    }

    return left_bottom;
}

Point GraphicPoints::find_right_upper()
{
    if (this->points.size() == 0)
        return {0.0, 0.0};

    Point right_upper = {std::get<0>(this->points[0]).x, std::get<0>(this->points[0]).y};

    for (std::size_t i = 0; i < this->points.size(); i++)
    {
        if (std::get<0>(this->points[i]).x > right_upper.x)
            right_upper.x = std::get<0>(this->points[i]).x;

        if (std::get<0>(this->points[i]).y > right_upper.y)
            right_upper.y = std::get<0>(this->points[i]).y;
    }

    return right_upper;
}

