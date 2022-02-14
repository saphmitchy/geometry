#ifndef GEOMETRY_LINE_HPP_
#define GEOMETRY_LINE_HPP_

#include <algorithm>
#include <cmath>
#include <cassert>
#include <utility>

#include "config.hpp"
#include "point.hpp"

namespace sapphre15 {

namespace geometry {

class Segment;
class Line {
    protected:
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
    // 点p を通り，傾き alpha の直線
    Line(const Point &p, Real alpha);
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
    Real slope();
    // 直線は平行か
    bool is_horizontal();
    // 直線は垂直か
    bool is_vertical();

    friend Point projection(const Line &l, const Point &p);
    friend Real angle(const Line &a, const Line &b);
    friend bool parallel(const Line &a, const Line &b);
    friend bool orthogonal(const Line &a, const Line &b);
    template<class S, class T>
    friend bool intersection(const S &a, const T &b);
};

class Segment : public Line {
    public:
    Segment() : Line() {}
    // 点 start, end を結ぶ線分
    Segment(const Point &_start, const Point &_end)
    : Line(_start, _end) {}
    // 点 start を始点とする長さ length 、傾き alpha の線分
    Segment(const Point &_start, const Real alpha, const Real length);

    // 始点を返す
    Point start();
    // 終点を返す
    Point end();
    // 始点のx座標
    double x1();
    // 始点のy座標
    double y1();
    // 終点のx座標
    double x2();
    // 終点のy座標
    double y2();
    // 線分のx方向の幅
    double dx();
    // 線分のy方向の幅
    double dy();
    // 線分の長さ
    double length();
    bool on_object(const Point &p) const {
        return ccw(_a, _b, p) == ON_SEGMENT;
    }
    // 端点を返す
    std::pair<Point, Point> end_points() const {
        return std::make_pair(_a, _b);
    }
};

class Ray : public Line {
    public:
    // 半直線の始点
    Point source();
    // 始点のx座標
    double x();
    // 始点のy座標
    double y();
    bool on_object(const Point &p);
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

/**
 * @brief 2直線のなす角を返す。返り値は0とPI/2の間
 * @return Real
 */
Real angle(const Line &a, const Line &b) {
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
bool parallel(const Line &a, const Line &b) {
    return eq(cross(a._a - a._b, b._a - b._b), 0.0);
}

/**
 * @brief 2直線が垂直かを返す
 * verified with https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_A
 * @return true 
 */
bool orthogonal(const Line &a, const Line &b) {
    return eq(dot(a._a - a._b, b._a - b._b), 0.0);
}

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_LINE_HPP_