#include <iostream>
#include <iomanip>

#include "point.hpp"
#include "polygon.hpp"

using namespace std;
using namespace sapphre15::geometry;

int main() {
    int n; cin >> n;
    vector<Point> buff(n);
    for(auto &p : buff) cin >> p;
    printf("%.1lf\n", Polygon(buff).area());
}