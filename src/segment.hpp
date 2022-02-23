#ifndef GEOMETRY_SEGMENT_HPP_
#define GEOMETRY_SEGMENT_HPP_

#include <cmath>
#include <utility>

#include "config.hpp"
#include "point.hpp"
#include "line.hpp"

namespace sapphre15 {

namespace geometry {

class Segment : public Line {
    public:
    Segment() : Line() {}
    // 点 start, end を結ぶ線分
    Segment(const Point &_start, const Point &_end)
    : Line(_start, _end) {}
    // 点 start を始点とする長さ length 、傾き theta の線分
    Segment(const Point &_start, const Real _theta, const Real _length)
    : Line(_start, _start + Point::polar(_theta, _length)) {}

    // 始点を返す
    Point start() const {
        return _a;
    }
    // 終点を返す
    Point end() const {
        return _b;
    }
    // 始点のx座標
    double x1() const {
        return _a.x();
    }
    // 始点のy座標
    double y1() const {
        return _a.y();
    }
    // 終点のx座標
    double x2() const {
        return _b.x();
    }
    // 終点のy座標
    double y2() const {
        return _b.y();
    }
    // 線分のx方向の幅
    double dx() const {
        return std::abs(_a.x() - _b.x());
    }
    // 線分のy方向の幅
    double dy() const {
        return std::abs(_a.y() - _b.y());
    }
    // 線分の長さ
    double length() {
        return abs(_a - _b);
    }
    bool on_object(const Point &p) const {
        return ccw(_a, _b, p) == ON_SEGMENT;
    }
    // 端点を返す
    std::pair<Point, Point> end_points() const {
        return std::make_pair(_a, _b);
    }
};

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_SEGMENT_HPP_