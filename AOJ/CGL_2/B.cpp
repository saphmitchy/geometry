#include <iostream>

#include "intersection.hpp"
#include "segment.hpp"

using namespace std;
using namespace sapphre15::geometry;

int ans[1100];

int main() {
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        Point p0, p1, p2, p3;
        cin >> p0 >> p1 >> p2 >> p3;
        ans[i] = intersection(Segment(p0, p1), Segment(p2, p3));
    }
    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
}