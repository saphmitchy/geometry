#ifndef GEOMETRY_CROSS_POINT_HPP_
#define GEOMETRY_CROSS_POINT_HPP_

#include <algorithm>
#include <cassert>
#include <utility>
#include <type_traits>
#include <vector>

#include "config.hpp"
#include "point.hpp"
#include "line.hpp"
#include "segment.hpp"

namespace sapphre15 {

namespace geometry {

std::vector<Point> cross_point(const Line &a, const Line &b) {
    assert(!parallel(a, b));
    Point da = a._b - a._a,
          db = b._b - b._a;
    return { a._a - da / cross(da, db) * cross(a._a - b._a, db)};
}

std::vector<Point> cross_point(const Segment &a, const Line &b) {
    std::vector<Point> ret = cross_point((Line)a, b);
    if(a.on_object(ret[0])) return ret;
    else return {};
}

std::vector<Point> cross_point(const Line &a, const Segment &b) {
    return cross_point(b, a);
}


// verified with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_C
std::vector<Point> cross_point(const Segment &a, const Segment &b) {
    std::vector<Point> ret = cross_point((Line)a, (Line)b);
    if(a.on_object(ret[0]) && b.on_object(ret[0])) return ret;
    else return {};
}

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_CROSS_POINT_HPP_