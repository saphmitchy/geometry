#ifndef GEOMETRY_DISTANCE_HPP_
#define GEOMETRY_DISTANCE_HPP_

#include <algorithm>
#include <utility>
#include <type_traits>

#include "config.hpp"
#include "point.hpp"
#include "line.hpp"
#include "segment.hpp"
#include "intersection.hpp"

namespace sapphre15 {

namespace geometry {

Real distance(const Line &l, const Point &p) {
    return std::abs(cross(l._a - p, l._b - p)) / abs(l._a - l._b);
}

Real distance(const Point &p, const Line &l) {
    return distance(l, p);
}

Real distance(const Line &l1, const Line &l2) {
    return parallel(l1, l2) ? distance(l1, l2._a) : 0;
}

Real distance(const Segment &l, const Point &p) {
    auto dd = dot(p - l.start(), l.end() - l.start());
    if(0 <= dd &&
        dd <= norm(l.end() - l.start())) {
        return distance((Line) l, p);
    } else {
        return std::min(distance(l.start(), p),
                        distance(l.end(), p));
    }
}

Real distance(const Point &p, const Segment &l) {
    return distance(l, p);
}

Real distance(const Segment &l1, const Line &l2) {
    if(intersection(l1, l2)) {
        return 0;
    } else {
        return std::min(distance(l2, l1.start()),
                        distance(l2, l1.end()));
    }
}

Real distance(const Line &l1, const Segment &l2) {
    return distance(l2, l1);
}

// verified with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_D
Real distance(const Segment &l1, const Segment &l2) {
    if(intersection(l1, l2)) return 0.0;
    else return std::min({distance(l1, l2.start()),
                          distance(l1, l2.end()  ),
                          distance(l2, l1.start()),
                          distance(l2, l1.end())});
}

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_DISTANCE_HPP_