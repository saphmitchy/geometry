#ifndef GEOMETRY_LINE_HPP_
#define GEOMETRY_LINE_HPP_

#include <cmath>
#include <cassert>

#include "config.hpp"
#include "point.hpp"

namespace sapphre15 {

namespace geometry {

class Line {
    Point _a, _b;
    public:
    // x+y = 1
    Line() : _a(1, 0), _b(0, 1) {}
    // 点a, bを結ぶ直線
    Line(const Point &a, const Point &b)
    : _a(a), _b(b) {}
    // ax + by + c = 0
    Line(const Real &a, const Real &b, const Real &c) {
        assert(!eq(a, 0.0) || !eq(b, 0.0));
        if(eq(a, 0.0)) {
            _a = Point(0.0, -c/b);
            _b = Point(1.0, -c/b);
        } else {
            _a = Point(-c/a, 0.0);
            _b = Point(-(c + b)/a, 1.0);
        }
    }

    // 直線上に点があるかを判定する
    bool on_line(const Point &p) const {
        ClockWise val = ccw(_a, _b, p);
        return val != CLOCKWISE && val != COUNTER_CLOCKWISE;
    }

    friend Point projection(const Line &l, const Point &p);
};


/**
 * @brief 直線 l に 点 p を射影した点を返す
 * verified with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_A
 * @param l 直線
 * @param p 点
 * @return Point 
 */
Point projection(const Line &l, const Point &p) {
    const Point a = p - l._a, b = l._b - l._a;
    return l._a + b * dot(a, b) / norm(b);
}

/**
 * @brief 直線 l に対して点 p と対称な点を返す
 * verified with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_B
 * @param l 直線
 * @param p 点
 * @return Point 
 */
Point reflection(const Line &l, const Point &p) {
    Point q = projection(l, p);
    return q * 2 - p;
}

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_LINE_HPP_