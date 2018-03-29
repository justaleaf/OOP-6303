#pragma once
#include "shape.h"
#include "point.h"

class Triangle : public Shape
{
public:
    Triangle(Point _A, Point _B, Point _C);
    void move(Point point);
    void turn(Point point, double angle);
    void scale(double k);
    void set_color(string color);
    string get_color();
    int get_id();
    Point find_center();
    double find_square();
    friend ostream& operator<<(std::ostream& stream, Triangle& triangle);

private:
    Point vertexes[3];
    int objID;
};
