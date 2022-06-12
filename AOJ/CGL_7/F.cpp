#include <iostream>
#include <iomanip>
#include <vector>

#include "point.hpp"
#include "circle.hpp"
#include "tangent.hpp"

using namespace std;
using namespace sapphre15::geometry;

int main() {
    Point p, c;
    Real r;
    cin >> p >> c >> r;
    Circle c1(c, r);
    vector<Point> ans = tangent(c1, p);
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
         << ans[0].y() << endl
         << ans[1].x() << " "
         << ans[1].y() << endl;
}
