#pragma once
#include <iostream>

class Point { //вспомогательный класс точка
public:
    Point();
    Point(double _x, double _y);
    Point(const Point& another);
    void setPoint(double, double);
    void setX(double);
    void setY(double);
    double getX() const;
    double getY() const;
    Point& operator=(const Point& p);
    friend std::ostream& operator << (std::ostream&, const Point&);
    ~Point();
private:
    double x;
    double y;
};
