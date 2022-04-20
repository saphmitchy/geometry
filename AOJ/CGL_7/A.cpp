#include <iostream>

#include "src/point.hpp"
#include "src/circle.hpp"
#include "src/intersection.hpp"

using namespace std;
using namespace sapphre15::geometry;

int main() {
    Point c1, c2;
    Real r1, r2;
    cin >> c1 >> r1 >> c2 >> r2;
    cout << intersection(Circle(c1, r1), Circle(c2, r2)) << endl;
}
