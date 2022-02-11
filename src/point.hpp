#ifndef GEOMETRY_POINT_HPP_
#define GEOMETRY_POINT_HPP_

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
        return abs(_x - q._x);
    }

    Real ydist(const Point &q) const {
        return abs(_y - q._y);
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

enum ClockWise {
    CLOCKWISE,
    COUNTER_CLOCKWISE,
    ONLINE_BACK,
    ONLINE_FRONT,
    ON_SEGMENT
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

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_POINT_HPP_