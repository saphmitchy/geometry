#ifndef GEOMETRY_CIRCLE_HPP_
#define GEOMETRY_CIRCLE_HPP_


#include "config.hpp"
#include "point.hpp"

namespace sapphre15 {

namespace geometry {

class Polygon {
    public:
    Polygon();
    // Container に含まれている点を順に並べた多角形
    template<class Container>
    Polygon(Container &&point_list);

    // 点pは多角形の内部にあるか
    bool inside(const Point &p);
    // 点pは多角形の境界上にあるか
    bool on_object(const Point &p);
    // 点pは多角形の外部にあるか
    bool outside(const Point &p);
    // 多角形は単純か
    bool is_simple();
    // 多角形は凸か
    bool is_convex();
    // 多角形をxだけ反時計回りに回転させる
    void rotate(const Real &x);
};

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_CIRCLE_HPP_