#ifndef GEOMETRY_LINE_HPP_
#define GEOMETRY_LINE_HPP_

#include <cmath>
#include <cassert>
#include <utility>
#include <vector>

#include "config.hpp"
#include "point.hpp"

namespace sapphre15 {

namespace geometry {

Point projection(const internal::LineBase &l, const Point &p);
Real angle(const internal::LineBase &a, const internal::LineBase &b);
bool parallel(const internal::LineBase &a, const internal::LineBase &b);
bool orthogonal(const internal::LineBase &a, const internal::LineBase &b);

namespace internal {

// parent namespace
namespace PARENT = ::sapphre15::geometry;

/**
 * @brief Base class of line like classes
 */
class LineBase {
    protected:
    Point _a, _b;
    public:
    virtual ~LineBase() {}

    // x+y = 1
    LineBase() : _a(1, 0), _b(0, 1) {}
    // 点a, bを結ぶ直線
    LineBase(const Point &a, const Point &b)
    : _a(a), _b(b) {}
    // ax + by + c = 0
    LineBase(const Real &a, const Real &b, const Real &c) {
        assert(!eq(a, 0.0) || !eq(b, 0.0));
        if(eq(a, 0.0)) {
            _a = Point(0.0, -c/b);
            _b = Point(1.0, -c/b);
        } else {
            _a = Point(-c/a, 0.0);
            _b = Point(-(c + b)/a, 1.0);
        }
    }
    // 点p を通り，偏角 theta の直線
    LineBase(const Point &p, const Real theta)
    : _a(p), _b(p + Point::polar(theta)) {}
    // 直線上に点があるかを判定する
    bool on_line(const Point &p) const {
        ClockWise val = ccw(_a, _b, p);
        return val != CLOCKWISE && val != COUNTER_CLOCKWISE;
    }
    // 直線の単位方向ベクトルを返す
    Point direction() const  {
        return (_b - _a) / abs(_b - _a);
    }
    // 図形上に点があるか
    virtual bool on_object(const Point &p) const {
        return on_line(p);
    }
    // 直線の傾き
    Real slope() const {
        return (_a.y() - _b.y()) / (_a.x() - _b.x());
    }
    // 直線は平行か
    bool is_horizontal() const {
        return eq(_a.y(), _b.y()); 
    }
    // 直線は垂直か
    bool is_vertical() const {
        return eq(_a.x(), _b.x()); 
    }

    friend Point PARENT::projection(const LineBase &l, const Point &p);
    friend Real PARENT::angle(const LineBase &a, const LineBase &b);
    friend bool PARENT::parallel(const LineBase &a, const LineBase &b);
    friend bool PARENT::orthogonal(const LineBase &a, const LineBase &b);
};

} // namespace internal

/**
 * @brief Line class
 */
class Line : public internal::LineBase {
    public:
    /**
     * @brief Construct a new Line object. x + y = 1.
     */
    Line() : internal::LineBase() {}
    /**
     * @brief Construct a new Line object that
     * pass through point a and b.
     * @param a Point
     * @param b Point
     */
    Line(const Point &a, const Point &b) : internal::LineBase(a, b) {}
    /**
     * @brief Construct a new Line object. ax + by + c = 0
     * @param a Real
     * @param b Real
     * @param c Real
     */
    Line(const Real &a, const Real &b, const Real &c)
    : internal::LineBase(a, b, c) {}
    // line that pass through point p and 
    /**
     * @brief Construct a new Line object that
     * pass through point p and
     * argument angle is theta.
     * @param p Point
     * @param theta argument angle in radian
     */
    Line(const Point &p, const Real theta)
    : internal::LineBase(p, theta) {}
    /**
     * @brief down cast from LineBase to Line
     * @param l LineBase
     */
    Line(const internal::LineBase &l)
    : internal::LineBase(l) {}
    /**
     * @brief return line that is translated by v
     * @param v vector of traslation
     * @return Line 
     */
    Line translation(const Point &v) const {
        return Line(_a + v, _b + v);
    }
    /**
     * @brief return line that is translated by dist to x-axis direction.
     * @param dist distance to translate
     * @return Line 
     */
    Line moveX(const Real &dist) const {
        return translation(Point(dist, 0.0));
    }
    /**
     * @brief return line that is translated by dist to y-axis direction.
     * @param dist distance to translate
     * @return Line 
     */
    Line moveY(const Real &dist) const {
        return translation(Point(0.0, dist));
    }

    friend std::vector<Point> cross_point(const Line &a, const Line &b);
    friend bool intersection(const Segment &a, const Line &b);
    friend Real distance(const Line &a, const Point &b);
    friend Real distance(const Line &a, const Line &b);
};

/**
 * @brief 直線 l に 点 p を射影した点を返す
 * verified with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/1/CGL_1_A
 * @param l 直線
 * @param p 点
 * @return Point 
 */
Point projection(const internal::LineBase &l, const Point &p) {
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
Point reflection(const internal::LineBase &l, const Point &p) {
    Point q = projection(l, p);
    return q * 2 - p;
}

/**
 * @brief 2直線のなす角を返す。返り値は0とPI/2の間
 * @return Real
 */
Real angle(const internal::LineBase &a, const internal::LineBase &b) {
    static const Real HALF_OF_SQRT2 = 0.70710678;
    Point u = a._a - a._b, v = b._a - b._b;
    Real val = std::abs(dot(u, v)) / abs(u) / abs(v);
    // arccos を用いると1付近での精度が落ちるので arcsin に切り替える
    if(val < HALF_OF_SQRT2) return std::acos(val);
    else return std::asin(std::abs(cross(u, v)) / abs(u) / abs(v));
}

/**
 * @brief 2直線が平行かを返す
 * verified with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_A
 * @return true 
 */
bool parallel(const internal::LineBase &a, const internal::LineBase &b) {
    return eq(cross(a._a - a._b, b._a - b._b), 0.0);
}

/**
 * @brief 2直線が垂直かを返す
 * verified with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_A
 * @return true 
 */
bool orthogonal(const internal::LineBase &a, const internal::LineBase &b) {
    return eq(dot(a._a - a._b, b._a - b._b), 0.0);
}

Real distance(const Line &l, const Point &p) {
    return std::abs(cross(l._a - p, l._b - p)) / abs(l._a - l._b);
}

Real distance(const Point &p, const Line &l) {
    return distance(l, p);
}

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_LINE_HPP_