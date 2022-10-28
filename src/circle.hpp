#ifndef GEOMETRY_CIRCLE_HPP_
#define GEOMETRY_CIRCLE_HPP_

#include <cassert>
#include <cmath>

#include "config.hpp"
#include "point.hpp"

namespace sapphre15 {

namespace geometry {

class Circle {
   public:
    Circle() : _center(), _radius(1.0) {
    }
    // 3点 c を中心として半径 r の円
    Circle(const Point &c, const Real &r) : _center(c), _radius(r) {
        assert(r >= 0);
    }
    // 3点 c を中心として点 a を通る円
    Circle(const Point &c, const Point &a) : _center(c), _radius(abs(c - a)) {
    }
    // 3点 a, b, c を通る円
    // verified with
    // https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_C
    Circle(const Point &a, Point b, Point c) {
        b -= a;
        c -= a;
        _center = Point(norm(b) * c.y() - norm(c) * b.y(),
                        norm(c) * b.x() - norm(b) * c.x()) /
                  cross(b, c) / 2.0;
        _center += a;
        _radius = distance(_center, a);
    }

    // 円の中心
    Point center() const {
        return _center;
    }
    // 円の半径
    Real radius() const {
        return _radius;
    }
    // 点pは円の内部か(境界を含む)
    bool inside(const Point &p) const {
        return le(distance(_center, p), _radius);
    }
    // 点pは円の外部か
    bool outside(const Point &p) const {
        return !le(distance(_center, p), _radius);
    }
    // 点pは円周上か
    bool on_object(const Point &p) const {
        return eq(_radius, distance(_center, p));
    }

   public:
    Point _center;
    Real  _radius;
};

/**
 * @brief return incircle of the three points.
 * verified with
 * https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/7/CGL_7_B
 * @param a Point
 * @param b Point
 * @param c Point
 * @return Circle
 */
Circle incircle(const Point &a, const Point &b, const Point &c) {
    Real ab = distance(a, b), bc = distance(b, c), ca = distance(c, a),
         _s = std::abs(cross(a - c, b - c));
    return Circle((a * bc + b * ca + c * ab) / (ab + bc + ca),
                  _s / (ab + bc + ca));
}

}  // namespace geometry

}  // namespace sapphre15

#endif  // GEOMETRY_CIRCLE_HPP_