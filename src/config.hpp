#ifndef GEOMETRY_CONFIG_HPP_
#define GEOMETRY_CONFIG_HPP_

#include <cmath>

namespace sapphre15 {

namespace geometry {

// 座標を扱う型
using Real = double;

// 比較に用いる誤差定数
constexpr Real EPS = 1e-10;
// 円周率
const Real PI = std::acos(Real(-1.0));

// 符号関数
constexpr int sgn(Real a) {
    return (a < -EPS) ? -1 : (a > EPS) ? 1 : 0;
}
// 値の比較
bool eq(Real a, Real b) {
    if (std::abs(a) > 1.0)
        return std::abs((a - b) / a) < EPS;
    else
        return std::abs(a - b) < EPS;
}

// a <= b
bool le(Real a, Real b) {
    return a < b || eq(a, b);
}

class Point;
namespace internal {
class LineBase;
}  // namespace internal
class Line;
class Ray;
class Segment;
class Circle;
class Polygon;

}  // namespace geometry

}  // namespace sapphre15

#endif  // GEOMETRY_CONFIG_HPP_