#include "scale.h"
#include "qgraphicsview.h"


Scale::Scale()
{
    init();
}

void
Scale::init()
{
    this->left_bottom = {0.0, 0.0};
    this->right_upper = {0.0, 0.0};

    this->x_axis = NULL;
    this->y_axis = NULL;

    for (size_t i = 0; i < MARKS_COUNT; i++)
    {
        this->x_marks[i] = NULL;
        this->y_marks[i] = NULL;

        this->x_marks_text[i] = NULL;
        this->y_marks_text[i] = NULL;
    }
}

bool
Scale::is_empty()
{
    return this->x_axis == NULL;
}

void
Scale::clear()
{
    if (is_empty())
        return;

    this->scene->removeItem(this->x_axis);
    this->scene->removeItem(this->y_axis);

    for (size_t i = 0; i < MARKS_COUNT; i++)
    {
        this->scene->removeItem(this->x_marks[i]);
        this->scene->removeItem(this->y_marks[i]);

        this->scene->removeItem(this->x_marks_text[i]);
        this->scene->removeItem(this->y_marks_text[i]);
    }

    init();
}

void
Scale::set_params(std::pair<Point, Point> scope)
{
    this->left_bottom = scope.first;
    this->right_upper = scope.second;
}
void
Scale::draw()
{
    int width = this->view->width();
    int height = this->view->height();

    double d_x = right_upper.x - left_bottom.x;
    double d_y = right_upper.y - left_bottom.y;

    double d = d_x > d_y ? d_x : d_y;

    double value_step = d / (MARKS_COUNT - 1);

    double pixel_step_x = (width - 200) / (MARKS_COUNT - 1);
    double pixel_step_y = (height - 200) / (MARKS_COUNT - 1);

    this->x_axis = this->scene->addLine(100, height - BORDER, width, height - BORDER);
    this->y_axis = this->scene->addLine(BORDER, 0, BORDER, height - 100);

    for (size_t i = 0; i < MARKS_COUNT; i++)
    {
        int x_pixel_pos = 100 + pixel_step_x * i;
        int y_pixel_pos = height - 100 - pixel_step_y * i;


        double x_value = this->left_bottom.x + value_step * i;
        double y_value = this->left_bottom.y + value_step * i;

        char buffer[256] = {0};

        std::snprintf(buffer, 255, "%.2f", x_value);
        this->x_marks_text[i] = this->scene->addText(QString::fromStdString(buffer));

        std::snprintf(buffer, 255, "%.2f", y_value);
        this->y_marks_text[i] = this->scene->addText(QString::fromStdString(buffer));

        double x_text_width = this->x_marks_text[i]->boundingRect().width();
        double x_text_height = this->x_marks_text[i]->boundingRect().height();

        this->x_marks[i] = this->scene->addLine(
                x_pixel_pos,
                height - BORDER * 0.75,
                x_pixel_pos,
                height - BORDER * 1.25
            );

        this->x_marks_text[i]->setPos(
                x_pixel_pos - x_text_width / 2,
                height - x_text_height - 2
            );


        this->y_marks[i] = this->scene->addLine(
                BORDER * 0.75,
                y_pixel_pos,
                BORDER * 1.25,
                y_pixel_pos
            );

        this->y_marks_text[i]->setPos(
                0,
            y_pixel_pos - x_text_height / 2
            );
    }
}
