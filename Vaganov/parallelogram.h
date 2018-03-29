#pragma once
#include "shape.h"
#include "point.h"

class Parallelogram : public Shape
{
public:
    Parallelogram(Point _A, Point _B, Point _C, Point _D);
    void move(Point point);
    void turn(Point point, double angle);
    void scale(double k);
    void set_color(string color);
    string get_color();
    int get_id();
    Point find_center();
    double find_square();
    bool is_valid();
    friend ostream& operator<<(std::ostream& stream, Parallelogram& parallelogram);

private:
    Point vertexes[4];
    int objID;
};
