#include "hexagon.h"
#include <cmath>
using namespace std;

Hexagon::Hexagon(Point _center, Point _vertex){
    center = _center;
    vertex = _vertex;
    if (is_valid() == true){
        color = "white";
        objID = ID++;
        name = "hexagon";
    }
    else{
        center.setPoint(0,0);
        vertex.setPoint(0,0);
        objID = -1;
        name = "invalid hexagon";
    }
}

void Hexagon::move(Point point)
{
    Point newpoint (point.getX()-center.getX(), point.getY()-center.getY());
    vertex.setPoint(vertex.getX()+newpoint.getX(),vertex.getY()+newpoint.getY());
    center.setPoint(center.getX()+newpoint.getX(),center.getY()+newpoint.getY());
}

void Hexagon::turn(Point point, double degree)
{
    double buf_x, buf_y;
    double deg = degree*(3.14159/180);
    buf_x = point.getX() + (vertex.getX()-point.getX())*cos(deg)-(vertex.getY()-point.getY())*sin(deg);
    buf_y = point.getY() + (vertex.getX()-point.getX())*sin(deg)+(vertex.getY()-point.getY())*cos(deg);
    vertex.setPoint(buf_x,buf_y);
    buf_x = point.getX() + (center.getX()-point.getX())*cos(deg)-(center.getY()-point.getY())*sin(deg);
    buf_y = point.getY() + (center.getX()-point.getX())*sin(deg)+(center.getY()-point.getY())*cos(deg);
    center.setPoint(buf_x,buf_y);
}

void Hexagon::scale(double k)
{
    if (k >= 0){
        Point zero (0,0);
        Point bufcenter = center;
        move(zero);
        vertex.setPoint(vertex.getX()*k,vertex.getY()*k);
        move(bufcenter);
    }
    else
        cout << "Wrong scaling factor" << endl;
}

void Hexagon::set_color(string _color){
    color = _color;
}

string Hexagon::get_color(){
    return color;
}

int Hexagon::get_id(){
    return objID;

}

bool Hexagon::is_valid(){

    double radius = sqrt(pow(vertex.getX()-center.getX(),2)+pow(vertex.getY()-center.getY(),2));
    if (radius != 0)
        return true;
    return false;
}

ostream & operator<<(ostream & out, Hexagon & hexagon)
{
    out << "[Name]:" << hexagon.name << endl;
    out << "[Color]:" << hexagon.color << endl;
    out << "[Vertexes]:" << endl;
    out << "[Vertex 1]: (" << hexagon.vertex.getX() << " " << hexagon.vertex.getY() << ")" << endl;
    out << "[Center]:" << "(" << hexagon.center.getX() << " " << hexagon.center.getY() << ")" << endl;
    out << "[ID]:" << hexagon.objID << endl;
    return out;
}
