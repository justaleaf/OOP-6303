#pragma once
#include "point.h"
#include <string>

using namespace std;

class Shape {           //интерфейс для работы с фигурами
public:
    virtual void move(Point A) = 0;
    virtual void turn(Point point, double angle) = 0;
    virtual void scale(double factor) = 0;
    virtual void set_color(string color) = 0;
    virtual string get_color() = 0;
    virtual int get_id() = 0;
    friend ostream& operator<<(ostream& out, Shape& object);
    Point center;
    string name;
    string color;
    static int ID;

 };
