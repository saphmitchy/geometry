#ifndef GEOMETRY_INTERSECTION_HPP_
#define GEOMETRY_INTERSECTION_HPP_

#include <utility>
#include <type_traits>

#include "config.hpp"
#include "point.hpp"
#include "line.hpp"

namespace sapphre15 {

namespace geometry {

template<class T, class S>
bool intersection(const T &a, const S &b) {
    static_assert(std::is_base_of<Line, T>::value, "T must be Drived Line");
    static_assert(std::is_base_of<Line, S>::value, "S must be Drived Line");
    return false;
}

template<>
bool intersection<Line, Line>(const Line &a, const Line &b) {
    return !parallel(a, b);
}

template<>
bool intersection<Segment, Line>(const Segment &a, const Line &b) {
    std::pair<Point, Point> p = a.end_points();
    if(b.on_object(p.first) || b.on_object(p.second)) return true;
    return ccw(b._a, b._b, p.first) * ccw(b._a, b._b, p.second) < 0;
}

template<>
bool intersection<Line, Segment>(const Line &a, const Segment &b) {
    return intersection(b, a);
}

// verified with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_B
template<>
bool intersection(const Segment &a, const Segment &b) {
    return intersection<Segment, Line>(a, b) && intersection<Segment, Line>(b, a);
}

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_INTERSECTION_HPP_