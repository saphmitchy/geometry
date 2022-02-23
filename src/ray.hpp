#ifndef GEOMETRY_RAY_HPP_
#define GEOMETRY_RAY_HPP_

#include "config.hpp"
#include "point.hpp"
#include "line.hpp"

namespace sapphre15 {

namespace geometry {

class Ray : public Line {
    public:
    Ray() : Line() {}
    // 点 start を始点とし end を結ぶ半直線
    Ray(const Point &_start, const Point &_to)
    : Line(_start, _to) {}
    // 点 start を始点とする傾き theta の半直線
    Ray(const Point &_start, const Real theta)
    : Line(_start, _start + Point::polar(theta)) {}
    // 半直線の始点
    Point source() const {
        return _a;
    }
    // 始点のx座標
    double x() const {
        return _a.x();
    }
    // 始点のy座標
    double y() const {
        return _a.y();
    }
    bool on_object(const Point &p) const {
        ClockWise val = ccw(_a, _b, p);
        return val == ONLINE_FRONT || val == ON_SEGMENT;
    }
};

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_RAY_HPP_