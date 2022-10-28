#include <iostream>

#include "circle.hpp"
#include "intersection.hpp"
#include "point.hpp"

using namespace std;
using namespace sapphre15::geometry;

int main() {
    Point c1, c2;
    Real  r1, r2;
    cin >> c1 >> r1 >> c2 >> r2;
    cout << static_cast<int>(intersection(Circle(c1, r1), Circle(c2, r2)))
         << endl;
}
