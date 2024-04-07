#include "Research.h"

#include <stdio.h>
#include <sys/time.h>
#include <cmath>

#include "Point.h"

#define RESEARCHESCOUNT 1000
#define PI acos(-1.0)

unsigned long long
timeval_diff_ms(struct timeval *beg, struct timeval *end) {
    return (end->tv_sec * 1000000ULL + end->tv_usec) - \
            (beg->tv_sec * 1000000ULL + beg->tv_usec);
}

static int
dda(const Point &begin, const Point &end) {
    int steps = 0;

    int x1 = begin.get_x();
    int y1 = begin.get_y();

    int x2 = end.get_x();
    int y2 = end.get_y();

    int abs_dx = abs(x2 - x1);
    int abs_dy = abs(y2 - y1);

    if (abs_dx == 0 && abs_dy == 0) {
        return steps;
    }

    int length = abs_dx > abs_dy ? abs_dx : abs_dy;

    double d_x = double(x2 - x1) / length;
    double d_y = double(y2 - y1) / length;

    double x = x1;
    double y = y1;

    for (int i = 0; i < length; i++) {
        if (round(x + d_x) != round(x) && round(y + d_y) != round(y))
            steps++;

        x += d_x;
        y += d_y;
    }

    return steps;
}

static int
sign(int number) {
    if (number > 0) return 1;
    if (number < 0) return -1;
    return 0;
}

static int
bresenham_real(const Point &begin, const Point &end) {
    int steps = 0;

    int x = begin.get_x();
    int y = begin.get_y();

    int dx = end.get_x() - begin.get_x();
    int dy = end.get_y() - begin.get_y();

    if (dx == 0 && dy == 0) {
        return steps;
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

    int x_prev = x;
    int y_prev = y;

    for (int i = 0; i < dx + 1; i++) {
        if (e >= 0.0) {
            if (swap_occurred) x += sx;
            else y += sy;

            e -= 1.0;
        }
        if (swap_occurred) y += sy;
        else x += sx;

        if (x_prev != x && y_prev != y)
            steps++;

        x_prev = x;
        y_prev = y;

        e += slope;
    }

    return steps;
}

static int
bresenham_int(const Point &begin, const Point &end) {
    int steps = 0;

    int x = begin.get_x();
    int y = begin.get_y();

    int dx = end.get_x() - begin.get_x();
    int dy = end.get_y() - begin.get_y();

    if (dx == 0 && dy == 0) {
        return steps;
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

    int x_prev = x;
    int y_prev = y;

    for (int i = 0; i < dx + 1; i++) {
        if (e >= 0.0) {
            if (swap_occurred) x += sx;
            else y += sy;

            e -= 2 * dx;
        }
        if (swap_occurred) y += sy;
        else x += sx;

        if (x_prev != x && y_prev != y)
            steps++;

        x_prev = x;
        y_prev = y;

        e += 2 * dy;
    }

    return steps;
}

static int
bresenham_smooth(const Point &begin, const Point &end) {
    int steps = 0;

    int x = begin.get_x();
    int y = begin.get_y();

    int dx = end.get_x() - begin.get_x();
    int dy = end.get_y() - begin.get_y();

    if (dx == 0 && dy == 0) {
        return steps;
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

    int x_prev = x;
    int y_prev = y;

    for (int i = 0; i < dx + 1; i++) {
        if (e < w) {
            if (swap_occurred) y += sy;
            else x += sx;

            e += slope;
        } else {
            x += sx;
            y += sy;
            e -= w;
        }

        if (x_prev != x && y_prev != y)
            steps++;

        x_prev = x;
        y_prev = y;
    }

    return steps;
}


static double fraction_part(double x) {
    return x - floor(x);
}

static double reverse_fraction_part(double x) {
    return 1 - fraction_part(x);
}

static int
wu(const Point &begin, const Point &end) {
    int steps = 0;

    int x0 = begin.get_x();
    int y0 = begin.get_y();
    int x1 = end.get_x();
    int y1 = end.get_y();

    if (x0 == x1 && y0 == y1) {
        return steps;
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

    int xpxl1 = x_end;
    double y = y_end + slope;

    x_end = int(x1 + 0.5);
    int xpxl2 = x_end;

    for (int x = xpxl1; x < xpxl2; x++) {
        if (x < round(x1) && int(y) != int(y + slope))
            steps++;

        y += slope;
    }

    return steps;
}

void (*line_drawers[5])(QPainter &, const Point &, const Point &) {
        Lines::dda,
        Lines::bresenham_real,
        Lines::bresenham_int,
        Lines::bresenham_smooth,
        Lines::wu,
};

int
Research::time_research(QPainter &painter, QColor &color, char *filename) {
    FILE *file = fopen(filename, "w");

    QPen prev_pen = painter.pen();
    painter.setPen(color);

    struct timeval beg, end;
    Point center(0.0);
    double radius = 10000.0;
    double angle = 360.0 / RESEARCHESCOUNT;
    double delta = angle * PI / 180.0;

    for (size_t function_i = 0; function_i < 5; function_i++) {
        void (*line_drawer)(QPainter &, const Point &, const Point &) = line_drawers[function_i];
        double t = 0.0;

        unsigned long long function_sum = 0;

        for (int research_i = 0; research_i < RESEARCHESCOUNT; research_i++) {
            double x = center.get_x() + radius * cos(t);
            double y = center.get_y() - radius * sin(t);
            Point radial(int(round(x)), int(round(y)));

            gettimeofday(&beg, NULL);
            line_drawer(painter, center, radial);
            gettimeofday(&end, NULL);

            t += delta;
            function_sum += timeval_diff_ms(&beg, &end);
        }

        double average_time = function_sum / RESEARCHESCOUNT;

        fprintf(file, "%.12lf\n", average_time);
    }

    fclose(file);
    painter.setPen(prev_pen);
    return 0;
}

int (*steps_counters[5]) (const Point&, const Point&) {
        dda,
        bresenham_real,
        bresenham_int,
        bresenham_smooth,
        wu
};

int
Research::steps_research(char *filename) {
    FILE *file = fopen(filename, "w");


    Point center(0.0);
    double radius = 1000.0;
    double delta = 5.0 * PI / 180.0;

    for (size_t function_i = 0; function_i < 5; function_i++) {
        int (*steps_counter)(const Point&, const Point&) = steps_counters[function_i];
        double t = 0.0;

        for (int d = 0; d <= 90; d += 5) {
            double x = center.get_x() + radius * cos(t);
            double y = center.get_y() - radius * sin(t);
            Point radial(int(round(x)), int(round(y)));

            int steps = steps_counter(center, radial);

            fprintf(file, "%d\n", steps);
            t += delta;
        }
    }

    fclose(file);
    return 0;
}