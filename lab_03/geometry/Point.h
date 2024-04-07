#ifndef POINT_H
#define POINT_H


class Point {
private:
    int x;
    int y;
    int intensity;
public:
    Point(int x = 0, int y = 0, int intensity = 255) : x(x), y(y), intensity(intensity) {};
    Point(const Point &other);

    void move(double dx, double dy);
    void rotate(const Point &, double angle);
    void scale(const Point &, double kx, double ky);

    void operator+=(const Point &right);
    void operator/=(double k);

    inline int get_x() const { return x; }
    inline int get_y() const { return y; }
    inline int get_intensity() const { return intensity; }

};


#endif //POINT_H
