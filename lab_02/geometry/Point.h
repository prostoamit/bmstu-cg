#ifndef POINT_H
#define POINT_H


class Point {
private:
    double x;
    double y;
public:
    Point(double x = 0, double y = 0) : x(x), y(y) {};
    Point(const Point &other);

    void move(double dx, double dy);
    void rotate(const Point &, double angle);
    void scale(const Point &, double kx, double ky);

    void operator+=(const Point &right);
    void operator/=(double k);

    inline double get_x() const { return x; }
    inline double get_y() const { return y; }

};


#endif //POINT_H
