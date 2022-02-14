#ifndef GEOMETRY_CIRCLE_HPP_
#define GEOMETRY_CIRCLE_HPP_


#include "config.hpp"
#include "point.hpp"

namespace sapphre15 {

namespace geometry {

class Circle {
    public:
    Circle();
    // 3点 c を中心として半径 r の円
    Circle(const Point &c, const Real &r);
    // 3点 c を中心として点 a を通る円
    Circle(const Point &c, const Point &a);
    // 3点 a, b, c を通る円
    Circle(const Point &a, const Point &b, const Point &c);

    // 円の中心
    Point center();
    // 円の半径
    Real radius();
    // 点pは円の内部か
    bool inside(const Point &p);
    // 点pは円の外部か
    bool outside(const Point &p);
    // 点pは円周上か
    bool on_object(const Point &p);
};

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_CIRCLE_HPP_