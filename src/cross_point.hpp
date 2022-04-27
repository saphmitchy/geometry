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
#include "circle.hpp"
#include "intersection.hpp"

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

/**
 * @brief calculate cross points of the circle and the point.
 * verified with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_D
 * @param c Circle
 * @param l Point
 * @return std::vector<Point> 
 * If there are no cross points, returned vector is empty.
 * If the line touches the circle, it has one element.
 * Otherwise, it has two cross point.
 */
std::vector<Point> cross_point(const Circle &c, const Line &l) {
    auto d1 = distance(c.center(), l);
    auto v1 = l.direction() * sqrt(c.radius()*c.radius() - d1*d1),
         p1 = projection(l, c.center());
    switch (intersection(c, l)) {
    case IntersectionCL::CROSS:
        return {p1 + v1, p1 - v1};
        break;
    case IntersectionCL::TOUCH:
        return {projection(l, c.center())};
        break;
    case IntersectionCL::NOT_CROSS:
        return {};
        break;
    default:
        break;
    }
    return {};
}

/**
 * @brief calculate cross points of the point and the circle.
 * @param l Point
 * @param c Circle
 * @return std::vector<Point> 
 * If there are no cross points, returned vector is empty.
 * If the line touches the circle, it has one element.
 * Otherwise, it has two cross point.
 */
std::vector<Point> cross_point(const Line &l, const Circle &c) {
    return cross_point(c, l);
}

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_CROSS_POINT_HPP_