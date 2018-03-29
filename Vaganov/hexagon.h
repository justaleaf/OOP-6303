#pragma once
#include "shape.h"
#include "point.h"

class Hexagon : public Shape
{
public:
    Hexagon(Point _center, Point _vertex);
    void move(Point point);
    void turn(Point point, double angle);
    void scale(double k);
    void set_color(string color);
    string get_color();
    int get_id();
    bool is_valid();
    friend ostream& operator<<(std::ostream& stream, Hexagon& hexagon);

private:
    Point vertex;
    int objID;
};
