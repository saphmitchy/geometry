#include <iostream>

#include "point.hpp"
#include "line.hpp"

using namespace std;
using namespace sapphre15::geometry;

int ans[1100];

int main() {
    int q; cin >> q;
    for(int i = 0; i < q; i++) {
        Point p0, p1, p2, p3;
        cin >> p0 >> p1 >> p2 >> p3;
        Line l1(p0, p1), l2(p2, p3);
        if(parallel(l1, l2)) ans[i] = 2;
        else if(orthogonal(l1, l2)) ans[i] = 1;
        else ans[i] = 0;
    }
    for(int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
}