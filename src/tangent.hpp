#ifndef GEOMETRY_TANGENT_HPP_
#define GEOMETRY_TANGENT_HPP_

#include "circle.hpp"
#include "config.hpp"
#include "line.hpp"
#include "point.hpp"

namespace sapphre15 {

namespace geometry {

/**
 * @brief calculate the tangent points of the circle that
 * pass through the point.
 * verified with
 * https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_F
 * @param c Circle
 * @param p Point
 * @return std::vector<Point>
 */
std::vector<Point> tangent(const Circle &c, const Point &p) {
    if (c.on_object(p)) {
        return {p};
    } else if (c.inside(p)) {
        return {};
    } else {
        auto q      = p - c.center();
        auto nrm    = norm(q);
        auto r      = c.radius();
        auto dst    = std::sqrt(-fma(c.radius(), c.radius(), -nrm));
        auto center = c.center();
        return {Point(fma((fma(q.x(), r, q.y() * dst)), r / nrm, center.x()),
                      fma((fma(q.y(), r, -q.x() * dst)), r / nrm, center.y())),
                Point(fma((fma(q.x(), r, -q.y() * dst)), r / nrm, center.x()),
                      fma((fma(q.y(), r, q.x() * dst)), r / nrm, center.y()))};
    }
}

}  // namespace geometry

}  // namespace sapphre15

#endif  // GEOMETRY_TANGENT_HPP_
