#include <iostream>
#include <iomanip>

#include "src/segment.hpp"
#include "src/cross_point.hpp"

using namespace std;
using namespace sapphre15::geometry;

Point ans[1100];

int main() {
    int q; cin >> q;
    cout << fixed << setprecision(15);
    for(int i = 0; i < q; i++) {
        Point p0, p1, p2, p3;
        cin >> p0 >> p1 >> p2 >> p3;
        ans[i] = cross_point(Segment(p0, p1),
                             Segment(p2, p3))[0];
    }
    for(int i = 0; i < q; i++) {
        cout << ans[i].x() << " " << ans[i].y() << endl;
    }
}