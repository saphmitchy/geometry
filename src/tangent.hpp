#ifndef GEOMETRY_TANGENT_HPP_
#define GEOMETRY_TANGENT_HPP_

#include "config.hpp"
#include "point.hpp"
#include "line.hpp"
#include "circle.hpp"

namespace sapphre15 {

namespace geometry {

/**
 * @brief calculate the tangent points of the circle that
 * pass through the point.
 * verified with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_F
 * @param c Circle
 * @param p Point
 * @return std::vector<Point> 
 */
std::vector<Point> tangent(const Circle &c, const Point &p) {
    if(c.on_object(p)) {
        return {p};
    } else if(c.inside(p)) {
        return {};
    } else {
        auto q = p - c.center();
        auto nrm = norm(q);
        auto r = c.radius();
        auto dst = std::sqrt(nrm - c.radius() * c.radius());
        return {
            Point((q.x() * r + q.y() * dst) * r / nrm,
                  (q.y() * r - q.x() * dst) * r / nrm) + c.center(),
            Point((q.x() * r - q.y() * dst) * r / nrm,
                  (q.y() * r + q.x() * dst) * r / nrm) + c.center()};
    }
}

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_TANGENT_HPP_