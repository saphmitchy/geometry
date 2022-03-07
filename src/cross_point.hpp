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

template<class T, class S>
std::vector<Point> cross_point(const T &a, const S &b) {
    static_assert(std::is_base_of<Line, T>::value, "T must be Drived Line");
    static_assert(std::is_base_of<Line, S>::value, "S must be Drived Line");
    return {};
}

template<>
std::vector<Point> cross_point<Line, Line>(const Line &a, const Line &b) {
    assert(!parallel(a, b));
    Point da = a._b - a._a,
          db = b._b - b._a;
    return { a._a - da / cross(da, db) * cross(a._a - b._a, db)};
}

template<>
std::vector<Point> cross_point<Segment, Line>(const Segment &a, const Line &b) {
    std::vector<Point> ret = cross_point<Line, Line>(a, b);
    if(a.on_object(ret[0])) return ret;
    else return {};
}

template<>
std::vector<Point> cross_point<Line, Segment>(const Line &a, const Segment &b) {
    return cross_point<Segment, Line>(b, a);
}


// verified with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_C
template<>
std::vector<Point> cross_point<Segment, Segment>(const Segment &a, const Segment &b) {
    std::vector<Point> ret = cross_point<Line, Line>(a, b);
    if(a.on_object(ret[0]) && b.on_object(ret[0])) return ret;
    else return {};
}

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_CROSS_POINT_HPP_