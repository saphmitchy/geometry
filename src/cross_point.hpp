#ifndef GEOMETRY_CROSS_POINT_HPP_
#define GEOMETRY_CROSS_POINT_HPP_

#include <algorithm>
#include <cassert>
#include <type_traits>
#include <utility>
#include <vector>

#include "circle.hpp"
#include "config.hpp"
#include "intersection.hpp"
#include "line.hpp"
#include "point.hpp"
#include "segment.hpp"

namespace sapphre15 {

namespace geometry {

std::vector<Point> cross_point(const Line &a, const Line &b) {
    assert(!parallel(a, b));
    Point da = a._b - a._a, db = b._b - b._a;
    return {a._a - da / cross(da, db) * cross(a._a - b._a, db)};
}

std::vector<Point> cross_point(const Segment &a, const Line &b) {
    std::vector<Point> ret = cross_point((Line)a, b);
    if (a.on_object(ret[0]))
        return ret;
    else
        return {};
}

std::vector<Point> cross_point(const Line &a, const Segment &b) {
    return cross_point(b, a);
}

// verified with
// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_C
std::vector<Point> cross_point(const Segment &a, const Segment &b) {
    std::vector<Point> ret = cross_point((Line)a, (Line)b);
    if (a.on_object(ret[0]) && b.on_object(ret[0]))
        return ret;
    else
        return {};
}

/**
 * @brief calculate cross points of the circle and the point.
 * verified with
 * https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_D
 * @param c Circle
 * @param l Point
 * @return std::vector<Point>
 * If there are no cross points, returned vector is empty.
 * If the line touches the circle, it has one element.
 * Otherwise, it has two cross point.
 */
std::vector<Point> cross_point(const Circle &c, const Line &l) {
    auto d1 = distance(c.center(), l);
    auto v1 = l.direction() * sqrt(c.radius() * c.radius() - d1 * d1),
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

/**
 * @brief calculate corss point of the two circles.
 * @param c1 Circle
 * @param c2 Circle
 * @return std::vector<Point>
 */
std::vector<Point> cross_point(const Circle &c1, const Circle &c2) {
    /**
     * To calculate cross points, we consider the line
     * To calculate the intersection, consider a line
     * passing through the intersection of two circles.
     * The intersection of that line and the circle is what we want.
     * To simplify the calculation, translate the figure
     * so that the midpoint of the two circles is the origin.
     *
     * We assume that
     * c1 : (x - a/2)^2 + (y - b/2)^2 = r1^2
     * c2 : (x + a/2)^2 + (y + b/2)^2 = r2^2
     * The equation of the line that we want is
     * ax + by = (r2^2 - r1^2) / 2
     * If c = 0, the line is the vertical bisector of the centers.
     * Else, the line passes through two points,
     * (k(a + b),  k(-a + b)) and (k(a - b), k(a + b))
     * Here, k = (r2^2 - r1^2) / (a^2 + b^2) / 2.
     */
    // midpoint of the center
    Point _m = (c1.center() + c2.center()) / 2,
          // a = _d.x(), _b = d.y()
        _d      = (c1.center() - c2.center());
    Real r_diff = (c2.radius() * c2.radius() - c1.radius() * c1.radius()) / 2,
         _k = r_diff / norm(_d), _s = (_d.x() + _d.y()) * _k,
         _t = (_d.x() - _d.y()) * _k;
    if (eq(r_diff, 0.0)) {
        // if vertical bisector is implemented, we will replace.
        return cross_point(c1, Line(_m, _m + rotate(_d, PI / 2)));
    } else {
        return cross_point(c1, Line(Point(_s, -_t) + _m, Point(_t, _s) + _m));
    }
}

}  // namespace geometry

}  // namespace sapphre15

#endif  // GEOMETRY_CROSS_POINT_HPP_