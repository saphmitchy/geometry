#ifndef GEOMETRY_INTERSECTION_HPP_
#define GEOMETRY_INTERSECTION_HPP_

#include <utility>
#include <type_traits>

#include "config.hpp"
#include "point.hpp"
#include "line.hpp"
#include "segment.hpp"
#include "circle.hpp"

namespace sapphre15 {

namespace geometry {

/**
 * @brief determine if the two Line intersect
 * @param a Line
 * @param b Line
 * @return bool
 */
bool intersection(const Line &a, const Line &b) {
    return !parallel(a, b);
}

/**
 * @brief determine if the Line and the Segment intersect
 * @param a Segment
 * @param b Line
 * @return bool
 */
bool intersection(const Segment &a, const Line &b) {
    std::pair<Point, Point> p = a.end_points();
    if(b.on_object(p.first) || b.on_object(p.second)) return true;
    return ccw(b._a, b._b, p.first) * ccw(b._a, b._b, p.second) < 0;
}

/**
 * @brief determine if the Line and the Segment intersect
 * @param a Line
 * @param b Segment
 * @return bool
 */
bool intersection(const Line &a, const Segment &b) {
    return intersection(b, a);
}

/**
 * @brief determine if the two Segment intersect
// verified with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_B
 * @param a Segment
 * @param b Segment
 * @return bool
 */
bool intersection(const Segment &a, const Segment &b) {
    return intersection(a, (Line)b) && intersection(b, (Line)a);
}

/**
 * @brief discribe intersection of two circles
 */
enum class IntersectionCC {
    NOT_CROSS    = 4,
    CIRCUMSCRIBE = 3, // 外接
    INTERSECT    = 2,
    INSCRIBE     = 1, // 内接
    INCLUDE      = 0, // 包含
};

/**
 * @brief determine how the two circle intersect.
 * verified with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_A
 * @param a Circle
 * @param b Circle
 * @return IntersectionCC
 */
IntersectionCC intersection(const Circle &a, const Circle &b) {
    Real d1 = distance(a.center(), b.center()),
         d2 = a.radius() + b.radius(),
         d3 = std::abs(a.radius() - b.radius());
    if(eq(d1, d2)) return IntersectionCC::CIRCUMSCRIBE;
    else if(eq(d1, d3)) return IntersectionCC::INSCRIBE;
    else if(le(d2, d1)) return IntersectionCC::NOT_CROSS;
    else if(le(d1, d3)) return IntersectionCC::INCLUDE;
    else return IntersectionCC::INTERSECT;
}

/**
 * @brief discribe intersection of a circle and a line
 */
enum IntersectionCL {
    NOT_CROSS    = 2,
    TOUCH        = 1,
    CROSS        = 0,
};

/**
 * @brief determine if circle and line intersect
 * @param c Circle
 * @param l Line
 * @return IntersectionCL 
 */
IntersectionCL intersection(const Circle &c, const Line &l) {
    Real _d = distance(c.center(), l);
    if(eq(_d, c.radius())) return IntersectionCL::TOUCH;
    else if(le(_d, c.radius())) return IntersectionCL::CROSS;
    else return IntersectionCL::NOT_CROSS;
}

/**
 * @brief determine if circle and line intersect
 * @param l Line
 * @param c Circle
 * @return IntersectionCL 
 */
IntersectionCL intersection(const Line &l, const Circle &c) {
    return intersection(c, l);
}

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_INTERSECTION_HPP_