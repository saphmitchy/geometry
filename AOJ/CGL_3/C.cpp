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
    Polygon pl(buff);
    int q; cin >> q;
    vector<int> ans(q);
    for(auto &i : ans) {
        Point p; cin >> p;
        if(pl.on_object(p)) i = 1;
        else if(pl.inside(p)) i = 2;
        else i = 0;
    }
    for(auto &i : ans) cout << i << endl;
}
