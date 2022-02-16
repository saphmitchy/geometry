#ifndef GEOMETRY_POINT_HPP_
#define GEOMETRY_POINT_HPP_

#include <cassert>
#include <cmath>
#include <complex>
#include <iostream>
#include <utility>

#include "config.hpp"

namespace sapphre15 {

namespace geometry {

// 点を管理するクラス
class Point {
  public:
    using value_type = Real;
    constexpr Point() : _x(0), _y(0) {
    }

    constexpr Point(const value_type &xval, const value_type &yval)
        : _x(xval), _y(yval) {
    }

    constexpr value_type x() const {
        return _x;
    }

    constexpr void x(value_type val) {
        _x = std::move(val);
    }

    constexpr value_type y() const {
        return _y;
    }

    constexpr void y(value_type val) {
        _y = std::move(val);
    }

    constexpr Point &operator+=(const Point &rhs) {
        _x += rhs._x;
        _y += rhs._y;
        return *this;
    }

    constexpr Point &operator-=(const Point &rhs) {
        _x -= rhs._x;
        _y -= rhs._y;
        return *this;
    }

    constexpr Point &operator*=(const Point &rhs) {
        _x *= rhs._x;
        _y *= rhs._y;
        return *this;
    }

    constexpr Point &operator*=(const value_type &rhs) {
        _x *= rhs;
        _y *= rhs;
        return *this;
    }

    constexpr Point &operator/=(const Point &rhs) {
        _x /= rhs._x;
        _y /= rhs._y;
        return *this;
    }

    constexpr Point &operator/=(const value_type &rhs) {
        _x /= rhs;
        _y /= rhs;
        return *this;
    }

    constexpr void rotate(const Real &theta) {
        auto tmpx = _x, tmpy = _y;
        _x = tmpx * std::cos(theta) - tmpy * std::sin(theta);
        _y = tmpx * std::sin(theta) + tmpy * std::cos(theta);
    }

    Real distance(const Point &q) const {
        return std::hypot(_x - q._x, _y - q._y);
    }

    Real distance() const {
        return std::hypot(_x, _y);
    }

    Real xdist(const Point &q) const {
        return std::abs(_x - q._x);
    }

    Real ydist(const Point &q) const {
        return std::abs(_y - q._y);
    }

    constexpr static Point polar(const Real &theta) {
        return Point(std::cos(theta), std::sin(theta));
    }

    constexpr static Point polar(const Real &theta, const Real &rho) {
        return Point(rho * std::cos(theta), rho * std::sin(theta));
    }

  private:
    value_type _x, _y;
};

Point::value_type abs(const Point &p) {
    return p.distance();
}

Point::value_type arg(const Point &p) {
    return std::atan2(p.y(), p.x());
}

Point::value_type norm(const Point &p) {
    return p.x() * p.x() + p.y() * p.y();
}

constexpr Point operator+(const Point &lhs) {
    return lhs;
}

constexpr Point operator-(const Point &lhs) {
    return Point(lhs) *= -1;
}

constexpr Point operator+(const Point &lhs, const Point &rhs) {
    return Point(lhs) += rhs;
}

constexpr Point operator-(const Point &lhs, const Point &rhs) {
    return Point(lhs) -= rhs;
}

constexpr Point operator*(const Point &lhs, const Point &rhs) {
    return Point(lhs) *= rhs;
}

constexpr Point operator*(const Point &lhs, const Point::value_type &rhs) {
    return Point(lhs) *= rhs;
}

constexpr Point operator/(const Point &lhs, const Point &rhs) {
    return Point(lhs) /= rhs;
}

constexpr Point operator/(const Point &lhs, const Point::value_type &rhs) {
    return Point(lhs) /= rhs;
}

constexpr bool operator==(const Point &lhs, const Point &rhs) {
    return eq(lhs.x(), rhs.x()) && eq(lhs.y(), rhs.y());
}

constexpr bool operator!=(const Point &lhs, const Point &rhs) {
    return !(lhs == rhs);
}

std::istream &operator>>(std::istream &is, Point &p) {
    Real a, b;
    is >> a >> b;
    p = Point(a, b);
    return is;
}

std::ostream &operator<<(std::ostream &os, Point &p) {
    return os << '(' << p.x() << ',' << p.y() << ')';
}

constexpr Point rotate(const Point &p, const Real &theta) {
    Point ret(p);
    ret.rotate(theta);
    return ret;
}

Real distance(const Point &p, const Point &q) {
    return p.distance(q);
}

Real xdist(const Point &p, const Point &q) {
    return p.xdist(q);
}

Real ydist(const Point &p, const Point &q) {
    return p.ydist(q);
}

// ベクトル p, q の内積を計算する
Real dot(const Point &p, const Point &q) {
    return p.x() * q.x() + p.y() * q.y();
}

// ベクトル p, q の外積を計算する
Real cross(const Point &p, const Point &q) {
    return p.x() * q.y() - p.y() * q.x();
}

// 点 p と点 q を a : b に内分する点
Point internal_div(const Point &p, const Point &q, const Real &a, const Real &b) {
    assert(0 <= a);
    assert(0 <= b);
    assert(0 <= a + b);
    return (p * b + q * a) / (a + b);
}

// 点 p と点 q の中点
Point mid_point(const Point &p, const Point &q) {
    return internal_div(p, q, 1.0, 1.0);
}

// 点 p と点 q を a : b に外分する点
Point external_div(const Point &p, const Point &q, const Real &a, const Real &b) {
    assert(0 <= a);
    assert(0 <= b);
    assert(!eq(a, b));
    return (q * a - p * b) / (a - b);
}

Real co_circle_internal1(Point p, Point q, Point r, const Point &s) {
    p -= s;
    q -= s;
    r -= s;
    return cross(p, q) * norm(r) + 
           cross(q, r) * norm(p) +
           cross(r, p) * norm(q);
}

Real co_circle_internal2(Point p, Point q, Point r, const Point &s) {
    p -= s;
    q -= s;
    r -= s;
    return cross(p, q) + 
           cross(q, r) +
           cross(r, p);
}

// 3点 p, q, r を含むような最小の円は点 s を内部に含むか（境界を含まない）
bool in_circle(const Point &p, const Point &q, const Point &r, const Point &s) {
    return sgn(co_circle_internal1(p, q, r, s)) == sgn(co_circle_internal2(p, q, r, s));
}

// 3点 p, q, r を含むような最小の円は点 s を円周上に含むか
bool on_circle(const Point &p, const Point &q, const Point &r, const Point &s) {
    return eq(co_circle_internal1(p, q, r, s), 0);
}

// 3点 p, q, r を含むような最小の円の外部に点 s は位置するか
bool out_circle(const Point &p, const Point &q, const Point &r, const Point &s) {
    return sgn(co_circle_internal1(p, q, r, s)) == sgn(co_circle_internal2(p, q, r, s)) * -1;
}

enum ClockWise {
    ONLINE_FRONT = -2,
    CLOCKWISE = -1,
    ON_SEGMENT = 0,
    COUNTER_CLOCKWISE = +1,
    ONLINE_BACK = +2,
};

/**
 * @brief 点a, b, c がどのように並んでいるかを判定する
 * verified with https://onlinejudge.u-aizu.ac.jp/problems/CGL_1_C
 */
ClockWise ccw(const Point &a, Point b, Point c) {
    b -= a, c -= a;
    if(sgn(cross(b, c)) > 0) return COUNTER_CLOCKWISE;
    if(sgn(cross(b, c)) < 0) return CLOCKWISE;
    if(sgn(dot(b, c)) < 0)   return ONLINE_BACK;
    if(le(abs(c), abs(b))) return ON_SEGMENT;
    return ONLINE_FRONT;
}

// 3点 p, q, r が一直線上にあるか
bool colinear(const Point &p, const Point &q, const Point &r) {
    ClockWise state = ccw(p, q, r);
    return state != COUNTER_CLOCKWISE && state != CLOCKWISE;
}

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_POINT_HPP_