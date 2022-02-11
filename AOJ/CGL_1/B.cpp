#include <iostream>

#include "src/point.hpp"
#include "src/line.hpp"

using namespace std;
using namespace sapphre15::geometry;

Point ans[1010];

int main() {
    Point p0, p1;
    cin >> p0 >> p1;
    Line l(p0, p1);
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        Point p2; cin >> p2;
        ans[i] = reflection(l, p2);
    }
    for(int i = 0; i < q; i++) {
        printf("%.9lf %.9lf\n", ans[i].x(), ans[i].y());
    }
}
