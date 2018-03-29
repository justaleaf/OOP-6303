#include <QCoreApplication>
#include <iostream>
#include "hexagon.h"
#include "parallelogram.h"
#include "triangle.h"

using namespace std;

int main(int argc, char *argv[])
{
    Point A (0,0), B (1,1), C(3,3), D(4,4), E(1,2), F(4,5);
    QCoreApplication a(argc, argv);
    // Создание заведомо валидных фигур и их вывод
    Parallelogram v_parallelogram(A,B,C,D);
    Triangle v_triangle (A,E,F);
    Hexagon v_hexagon (C, F);
    v_hexagon.set_color("blue");
    cout << v_parallelogram;
    cout << v_triangle;
    cout << v_hexagon;
    cout << "Invalid shapes:" << endl;

    // Создание заведомо невалидных фигур и их вывод
    Parallelogram inv_parallelogram(A,E,B,F);
    Triangle inv_triangle(A,B,C);
    Hexagon inv_hexagon(D,D);
    cout << inv_parallelogram;
    cout << inv_triangle;
    cout << inv_hexagon;
    return a.exec();
}
