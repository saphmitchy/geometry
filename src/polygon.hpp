#ifndef GEOMETRY_CIRCLE_HPP_
#define GEOMETRY_CIRCLE_HPP_

#include <algorithm>
#include <iterator>
#include <memory>

#include "config.hpp"
#include "point.hpp"
#include "segment.hpp"
#include "intersection.hpp"

namespace sapphre15 {

namespace geometry {

class Polygon {
    public:
    /**
     * @brief Create a Polygon object whose vertex is
     * the points contained point_list.
     * The order is modified if the order is clockwise.
     * @tparam Container required foeward-interator.
     * @param points_list container object stored vertex.
     */
    template<class Container>
    Polygon(Container &&points_list)
    : _num(points_list.size()) {
        points.reset(new Point[_num]);
        std::copy(begin(points_list),
                  end(points_list),
                  begin(_points));
        // the order is checked.
        if(sgn(area()) < 0) {
            reverse(_points, _points + _num);
        }
    }
    
    /**
     * @brief calculate the area of the polygon.
     * @return Real 
     */
    Real area() const {
        Real val = 0.0;
        for(size_t i = 0; i < _num - 1; i++) {
            val += cross(_points[i], _points[i+1]);
        }
        return val / 2.0;
    }

    // 点pは多角形の内部にあるか
    bool inside(const Point &p) {
        Real sum = 0;
        for(size_t i = 1; i < _num; i++) {
            sum += cross(_points[i-1] - p, _points[i] - p);
        }
        sum += cross(_points[_num-1] - p, _points[0] - p);
        return eq(sum, 0.0);
    }
    // 点pは多角形の境界上にあるか
    bool on_object(const Point &p) {
        for(size_t i = 1; i < _num; i++) {
            if(ccw(_points[i-1], _points[i], p) == ON_SEGMENT) {
                return true;
            }
        }
        return ccw(_points[0], _points[_num-1], p) == ON_SEGMENT;
    }
    // 点pは多角形の外部にあるか
    bool outside(const Point &p) {
        return !inside(p);
    }
    // 多角形は単純か
    bool is_simple() {
        for(int i = 1; i < _num; i++) {
            for(int j = 1; j < i; j++) {
                if(intersection(Segment(_points[i-1], _points[i]),
                                Segment(_points[j-1], _points[j]))) {
                    return false;
                }
            }
        }
        return true;
    }
    // 多角形は凸か
    bool is_convex() {
        ClockWise init = ccw(_points[_num-1], _points[0], _points[1]);
        for(int i = 2; i < _num; i++) {
            if(init != ccw(_points[i-2], _points[i-1], _points[i])) {
                return false;
            }
        }
        return init == ccw(_points[_num-2], _points[_num-1], _points[0]);
    }

    private:
    // number of vertex
    const size_t _num;
    // list of vertexes
    // the order is counter-clockwise
    std::unique_ptr<Point[]> _points;
};

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_CIRCLE_HPP_
