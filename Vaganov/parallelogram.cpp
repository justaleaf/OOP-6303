#include "parallelogram.h"
#include <cmath>
using namespace std;

Parallelogram::Parallelogram(Point _A, Point _B, Point _C, Point _D){
    vertexes[0] = _A;
    vertexes[1] = _B;
    vertexes[2] = _C;
    vertexes[3] = _D;
    if (find_square() != 0 && is_valid() == true){
        color = "white";
        center = find_center();
        objID = ID++;
        name = "parallelogram";
    }
    else{
        Point zero(0, 0);
        for (int i = 0; i < 4; i++)
            vertexes[i] = zero;
        objID = -1;
        name = "invalid parallelogram";
    }
}

void Parallelogram::move(Point point)
{
    Point newpoint (point.getX()-center.getX(), point.getY()-center.getY());
    for (int i = 0; i < 4; i++)
        vertexes[i].setPoint(vertexes[i].getX()+newpoint.getX(),vertexes[i].getY()+newpoint.getY());
    center.setPoint(center.getX()+newpoint.getX(),center.getY()+newpoint.getY());
}

void Parallelogram::turn(Point point, double degree)
{
    double buf_x, buf_y;
    double deg = degree*(3.14159/180);
    for (int i = 0; i < 4; i++){
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

void Parallelogram::scale(double k)
{
    Point zero (0,0);
    Point bufcenter = center;
    move(zero);
    for (int i = 0; i < 4; i++)
        vertexes[i].setPoint(vertexes[i].getX()*k,vertexes[i].getY()*k);
    move(bufcenter);

    /*for (int i = 0; i < 3; i++)
        vertexes[i].setPoint(vertexes[i].getX()*k,vertexes[i].getY()*k);
    center = find_center();*/
}

void Parallelogram::set_color(string _color){
    color = _color;
}

string Parallelogram::get_color(){
    return color;
}

Point Parallelogram::find_center(){
    Point _center(((vertexes[0].getX()+vertexes[2].getX())/2),((vertexes[0].getY()+vertexes[2].getY())/2));
    return _center;
}

double Parallelogram::find_square(){
    double Xa = abs(vertexes[1].getX() - vertexes[0].getX()),
           Xb = abs(vertexes[1].getX() - vertexes[2].getX()),
           Ya = abs(vertexes[1].getY() - vertexes[0].getY()),
           Yb = abs(vertexes[1].getY() - vertexes[2].getY());
    double buffer = (Xa*Xb+Ya*Yb)/(sqrt(Xa*Xa+Ya*Ya)*sqrt(Xb*Xb+Yb*Yb));
    double square = sqrt(Xa*Xa+Ya*Ya)*sqrt(Xb*Xb+Yb*Yb)*sin(acos(buffer));
    return square;
}

int Parallelogram::get_id(){
    return objID;
}

bool Parallelogram::is_valid(){
    bool parallel = false;
    bool equals = false;
    double k1 = abs((vertexes[0].getY() - vertexes[1].getY()) / (vertexes[0].getX() - vertexes[1].getX()));
    double k2 = abs((vertexes[3].getY() - vertexes[2].getY()) / (vertexes[3].getX() - vertexes[2].getX()));
    double k3 = abs((vertexes[0].getY() - vertexes[3].getY()) / (vertexes[0].getX() - vertexes[3].getX()));
    double k4 = abs((vertexes[2].getY() - vertexes[1].getY()) / (vertexes[2].getX() - vertexes[1].getX()));
    if ((k1 == k2) && (k3 == k4))
        parallel = true;
    if ((abs(vertexes[0].getX() - vertexes[1].getX()) == abs(vertexes[2].getX() - vertexes[3].getX())) &&
        (abs(vertexes[0].getY() - vertexes[1].getY()) == abs(vertexes[2].getY() - vertexes[3].getY())))
        equals = true;
    return (parallel && equals);
}

ostream & operator<<(ostream & out, Parallelogram & parallelogram)
{
    out << "[Name]:" << parallelogram.name << endl;
    out << "[Color]:" << parallelogram.color << endl;
    out << "[Vertexes]:" << endl;
    out << "[Vertex 1]: (" << parallelogram.vertexes[0].getX() << " " << parallelogram.vertexes[0].getY() << ")" << endl;
    out << "[Vertex 2]: (" << parallelogram.vertexes[1].getX() << " " << parallelogram.vertexes[1].getY() << ")" << endl;
    out << "[Vertex 3]: (" << parallelogram.vertexes[2].getX() << " " << parallelogram.vertexes[2].getY() << ")" << endl;
    out << "[Vertex 4]: (" << parallelogram.vertexes[3].getX() << " " << parallelogram.vertexes[3].getY() << ")" << endl;
    out << "[Center]:" << "(" << parallelogram.center.getX() << " " << parallelogram.center.getY() << ")" << endl;
    out << "[ID]:" << parallelogram.objID << endl;
    return out;
}
