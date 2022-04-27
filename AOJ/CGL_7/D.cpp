#include <iostream>
#include <iomanip>
#include <vector>

#include "src/point.hpp"
#include "src/circle.hpp"
#include "src/cross_point.hpp"

using namespace std;
using namespace sapphre15::geometry;

vector<Point> ans[1100];

int main() {
    Point cnt; cin >> cnt;
    Real r; cin >> r;
    Circle c(cnt, r);
    int t; cin >> t;
    for(int i = 0; i < t; i++) {
        Point p1, p2; cin >> p1 >> p2;
        Line l(p1, p2);
        ans[i] = cross_point(c, l);

        if(ans[i].size() == 1) ans[i].push_back(ans[i][0]);
        else {
            if(eq(ans[i][0].x(), ans[i][1].x())) {
                if(le(ans[i][1].y(), ans[i][0].y())) {
                    swap(ans[i][0], ans[i][1]);
                }
            } else if(le(ans[i][1].x(), ans[i][0].x())) {
                swap(ans[i][0], ans[i][1]);
            }
        }
    }
    cout << setprecision(15) << fixed;
    for(int i = 0; i < t; i++) {
        cout << ans[i][0].x() << " "
             << ans[i][0].y() << " "
             << ans[i][1].x() << " "
             << ans[i][1].y() << endl;
    }
}