#include <iostream>
#include <iomanip>
#include <vector>

#include "src/point.hpp"
#include "src/circle.hpp"
#include "src/cross_point.hpp"

using namespace std;
using namespace sapphre15::geometry;

int main() {
    Point p1, p2;
    Real r1, r2;
    cin >> p1 >> r1 >> p2 >> r2;
    Circle c1(p1, r1), c2(p2, r2);
    vector<Point> ans = cross_point(c1, c2);
    if(ans.size() == 1) {
        ans.emplace_back(ans[0]);
    } else {
        if(eq(ans[0].x(), ans[1].x())) {
            if(le(ans[1].y() ,ans[0].y())) {
                swap(ans[0], ans[1]);
            }
        } else if(le(ans[1].x(), ans[0].x())) {
            swap(ans[0], ans[1]);
        }
    }
    cout << setprecision(15) << fixed;
    cout << ans[0].x() << " "
         << ans[0].y() << " "
         << ans[1].x() << " "
         << ans[1].y() << endl;
}