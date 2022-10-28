#include <iostream>

#include "point.hpp"

using namespace std;
using namespace sapphre15::geometry;

ClockWise ans[1010];

string output(const ClockWise &cw) {
    if (cw == CLOCKWISE) return "CLOCKWISE";
    if (cw == COUNTER_CLOCKWISE) return "COUNTER_CLOCKWISE";
    if (cw == ONLINE_BACK) return "ONLINE_BACK";
    if (cw == ONLINE_FRONT)
        return "ONLINE_FRONT";
    else
        return "ON_SEGMENT";
}

int main() {
    Point p0, p1;
    cin >> p0 >> p1;
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        Point p2;
        cin >> p2;
        ans[i] = ccw(p0, p1, p2);
    }
    for (int i = 0; i < q; i++) {
        cout << output(ans[i]) << endl;
    }
}
