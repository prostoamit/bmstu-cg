#include "Lines.h"

#include <math.h>

static int
sign(int number) {
    if (number > 0) return 1;
    if (number < 0) return -1;
    return 0;
}

static void
point_draw(QPainter &painter, int x, int y, int intensity) {
    QColor color = painter.pen().color();
    color.setAlpha(intensity);
    painter.setPen(color);

    painter.drawPoint(x, y);
}

void
Lines::dda(QPainter &painter, const Point &begin, const Point &end) {
    int x1 = begin.get_x();
    int y1 = begin.get_y();

    int x2 = end.get_x();
    int y2 = end.get_y();

    int abs_dx = abs(x2 - x1);
    int abs_dy = abs(y2 - y1);

    if (abs_dx == 0 && abs_dy == 0) {
        painter.drawPoint(x1, y1);
        return;
    }

    int length = abs_dx > abs_dy ? abs_dx : abs_dy;

    double d_x = double(x2 - x1) / length;
    double d_y = double(y2 - y1) / length;

    double x = x1;
    double y = y1;

    for (int i = 0; i < length; i++) {
        painter.drawPoint(int(round(x)), int(round(y)));
        x += d_x;
        y += d_y;
    }
}

void
Lines::bresenham_real(QPainter &painter, const Point &begin, const Point &end) {
    int x = begin.get_x();
    int y = begin.get_y();

    int dx = end.get_x() - begin.get_x();
    int dy = end.get_y() - begin.get_y();

    if (dx == 0 && dy == 0) {
        painter.drawPoint(x, y);
        return;
    }

    int sx = sign(dx);
    int sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    int swap_occurred = 0;
    if (dy > dx) {
        int tmp = dx;
        dx = dy;
        dy = tmp;

        swap_occurred = 1;
    }

    double slope = double(dy) / double(dx);
    double e = slope - 0.5;

    for (int i = 0; i < dx + 1; i++) {
        painter.drawPoint(x, y);
        if (e >= 0.0) {
            if (swap_occurred) x += sx;
            else y += sy;

            e -= 1.0;
        }
        if (swap_occurred) y += sy;
        else x += sx;

        e += slope;
    }
}

void
Lines::bresenham_int(QPainter &painter, const Point &begin, const Point &end) {
    int x = begin.get_x();
    int y = begin.get_y();

    int dx = end.get_x() - begin.get_x();
    int dy = end.get_y() - begin.get_y();

    if (dx == 0 && dy == 0) {
        painter.drawPoint(x, y);
        return;
    }

    int sx = sign(dx);
    int sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    int swap_occurred = 0;
    if (dy > dx) {
        int tmp = dx;
        dx = dy;
        dy = tmp;

        swap_occurred = 1;
    }

    int e = 2 * dy - dx;

    for (int i = 0; i < dx + 1; i++) {
        painter.drawPoint(x, y);
        if (e >= 0) {
            if (swap_occurred) x += sx;
            else y += sy;

            e -= 2 * dx;
        }
        if (swap_occurred) y += sy;
        else x += sx;

        e += 2 * dy;
    }
}

void
Lines::bresenham_smooth(QPainter &painter, const Point &begin, const Point &end) {
    int x = begin.get_x();
    int y = begin.get_y();

    int dx = end.get_x() - begin.get_x();
    int dy = end.get_y() - begin.get_y();

    if (dx == 0 && dy == 0) {
        painter.drawPoint(x, y);
        return;
    }

    int sx = sign(dx);
    int sy = sign(dy);

    dx = abs(dx);
    dy = abs(dy);

    int swap_occurred = 0;
    if (dy > dx) {
        int tmp = dx;
        dx = dy;
        dy = tmp;

        swap_occurred = 1;
    }

    double intensity = 255;
    double slope = double(dy) / double(dx);
    double e = 0.5;
    double w = 1 - slope;

    for (int i = 0; i < dx + 1; i++) {
        point_draw(painter, x, y, e * intensity);

        if (e < w) {
            if (swap_occurred) y += sy;
            else x += sx;

            e += slope;
        } else {
            x += sx;
            y += sy;
            e -= w;
        }
    }
}

static double
fraction_part(double x) {
    return x - floor(x);
}

static double
reverse_fraction_part(double x) {
    return 1 - fraction_part(x);
}

void
Lines::wu(QPainter &painter, const Point &begin, const Point &end) {
    int x0 = begin.get_x();
    int y0 = begin.get_y();
    int x1 = end.get_x();
    int y1 = end.get_y();

    if (x0 == x1 && y0 == y1) {
        painter.drawPoint(x0, x1);
        return;
    }

    bool steep = abs(y1 - y0) > abs(x1 - x0);

    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int dx = x1 - x0;
    int dy = y1 - y0;
    double slope = (dx == 0) ? 1.0 : double(dy) / dx;

    int intensity = 255;

    int x_end = int(round(x0));
    int y_end = y0 + slope * (x_end - x0);

    int x_pix_left_1 = x_end;
    double current_y = y_end + slope;

    x_end = int(x1 + 0.5);
    int x_pix_left_2 = x_end;

    if (steep) {
        for (int x = x_pix_left_1; x < x_pix_left_2; x++) {
            int intensity_2 = int(fraction_part(current_y) * intensity);
            int intensity_1 = intensity - intensity_2;

            int current_i_y = int(current_y);

            point_draw(painter, current_i_y, x + 1, intensity_1);
            point_draw(painter, current_i_y + 1, x + 1, intensity_2);

            current_y += slope;
        }
    } else {
        for (int x = x_pix_left_1; x < x_pix_left_2; x++) {
            int intensity_2 = int(fraction_part(current_y) * intensity);
            int intensity_1 = intensity - intensity_2;

            int current_i_y = int(current_y);

            point_draw(painter, x + 1, current_i_y, intensity_1);
            point_draw(painter, x + 1, current_i_y + 1, intensity_2);

            current_y += slope;
        }
    }
}

void
Lines::library(QPainter &painter, const Point &begin, const Point &end) {
    painter.drawLine(begin.get_x(), begin.get_y(), end.get_x(), end.get_y());
}
