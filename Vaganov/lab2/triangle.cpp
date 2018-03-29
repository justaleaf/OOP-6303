#include "triangle.h"
#include <cmath>
using namespace std;

Triangle::Triangle(Point _A, Point _B, Point _C){
    vertexes[0] = _A;
    vertexes[1] = _B;
    vertexes[2] = _C;
    if (find_square() != 0){
        color = "white";
        center = find_center();
        objID = ID++;
        name = "triangle";
    }
    else{
        Point zero(0, 0);
        for (int i = 0; i < 3; i++)
            vertexes[i] = zero;
        objID = -1;
        name = "invalid triangle";
    }
}

void Triangle::move(Point point)
{
    Point newpoint (point.getX()-center.getX(), point.getY()-center.getY());
    for (int i = 0; i < 3; i++)
        vertexes[i].setPoint(vertexes[i].getX()+newpoint.getX(),vertexes[i].getY()+newpoint.getY());
    center.setPoint(center.getX()+newpoint.getX(),center.getY()+newpoint.getY());
}

void Triangle::turn(Point point, double degree)
{
    double buf_x, buf_y;
    double deg = degree*(3.14159/180);
    for (int i = 0; i < 3; i++){
        buf_x = point.getX() + (vertexes[i].getX()-point.getX())*cos(deg)-(vertexes[i].getY()-point.getY())*sin(deg);
        buf_y = point.getY() + (vertexes[i].getX()-point.getX())*sin(deg)+(vertexes[i].getY()-point.getY())*cos(deg);
        vertexes[i].setX(buf_x);
        vertexes[i].setY(buf_y);
    }
    buf_x = point.getX() + (center.getX()-point.getX())*cos(deg)-(center.getY()-point.getY())*sin(deg);
    buf_y = point.getY() + (center.getX()-point.getX())*sin(deg)+(center.getY()-point.getY())*cos(deg);
    center.setX(buf_x);
    center.setY(buf_y);
}

void Triangle::scale(double k)
{
    Point zero (0,0);
    Point bufcenter = center;
    move(zero);
    for (int i = 0; i < 3; i++)
        vertexes[i].setPoint(vertexes[i].getX()*k,vertexes[i].getY()*k);
    move(bufcenter);

    /*for (int i = 0; i < 3; i++)
        vertexes[i].setPoint(vertexes[i].getX()*k,vertexes[i].getY()*k);
    center = find_center();*/
}

void Triangle::set_color(string _color){
    color = _color;
}

string Triangle::get_color(){
    return color;
}

Point Triangle::find_center(){
    Point _center(0,0);
    for (int i = 0; i < 3; i++)
        _center.setPoint(((_center.getX()+vertexes[i].getX())* (1.0 / 3)),((_center.getY()+vertexes[i].getY())* (1.0 / 3)));
    return _center;
}

double Triangle::find_square(){
    Point a = vertexes[0];
    Point b = vertexes[1];
    Point c = vertexes[2];
    double square = 0.5*abs((b.getX() - a.getX())*(c.getY() - a.getY()) - (c.getX() - a.getX())*(b.getY() - a.getY()));
    return square;
}

int Triangle::get_id(){
    return objID;
}

ostream & operator<<(ostream & out, Triangle & triangle)
{
    out << "[Name]:" << triangle.name << endl;
    out << "[Color]:" << triangle.color << endl;
    out << "[Vertexes]:" << endl;
    out << "[Vertex 1]: (" << triangle.vertexes[0].getX() << " " << triangle.vertexes[0].getY() << ")" << endl;
    out << "[Vertex 2]: (" << triangle.vertexes[1].getX() << " " << triangle.vertexes[1].getY() << ")" << endl;
    out << "[Vertex 3]: (" << triangle.vertexes[2].getX() << " " << triangle.vertexes[2].getY() << ")" << endl;
    out << "[Center]:" << "(" << triangle.center.getX() << " " << triangle.center.getY() << ")" << endl;
    out << "[ID]:" << triangle.objID << endl;
    return out;
}
