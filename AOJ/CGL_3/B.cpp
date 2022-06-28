#include <iostream>

#include "point.hpp"
#include "polygon.hpp"

using namespace std;
using namespace sapphre15::geometry;

int main() {
    int n; cin >> n;
    vector<Point> buff(n);
    for(auto &p : buff) cin >> p;
    Polygon pl(buff);
    cout << (pl.is_convex() ? 1 : 0) << endl;
}
