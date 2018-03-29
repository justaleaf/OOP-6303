#include "point.h"
using namespace std;

Point::Point(): x(0.0),y(0.0){}

Point::Point(double _x, double _y): x(_x),y(_y){}

Point::Point(const Point &another){
    setPoint(another.getX(),another.getY());
}

Point::~Point() {}

void Point::setPoint(double _x, double _y){
    x = _x;
    y = _y;
}

void Point::setX (double _x) {
    x = _x;
}
void Point::setY (double _y) {
    y = _y;
}
double Point::getX () const {
    return x;
}
double Point::getY () const{
    return y;
}
Point& Point::operator=(const Point& p){
    if (this != &p){
        this->setX(p.getX());
        this->setY(p.getY());
    }
    return *this;
}
ostream & operator<<(ostream& stream, const Point & p){
    stream << " Point (" << p.x << " " << p.y << ")" << endl;
    return stream;
}


