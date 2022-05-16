#include <iostream>
#include <iomanip>

#include "point.hpp"
#include "circle.hpp"

using namespace std;
using namespace sapphre15::geometry;

int main() {
    Point p1, p2, p3;
    cin >> p1 >> p2 >> p3;
    Circle c(p1, p2, p3);
    cout << setprecision(15) << fixed;
    cout << c.center().x() << " " 
         << c.center().y() << " "
         << c.radius() << endl;
}