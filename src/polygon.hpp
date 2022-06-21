#ifndef GEOMETRY_POLYGON_HPP_
#define GEOMETRY_POLYGON_HPP_

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <vector>

#include "config.hpp"
#include "point.hpp"
#include "segment.hpp"
#include "intersection.hpp"

namespace sapphre15 {

namespace geometry {

class PolygonIterator;

class Polygon {
    public:
    /**
     * @brief Create a Polygon object whose vertex is
     * the points contained point_list.
     * The order is modified if the order is clockwise.
     * @param points_list 
     */
    Polygon(const std::vector<Point> &points_list)
    : _num(points_list.size()) {
        _points.reset(new Point[_num]);
        std::copy(std::begin(points_list),
                  std::end(points_list),
                  _points.get());
        // the order is checked.
        if(sgn(area()) < 0) {
            std::reverse(_points.get(), _points.get() + _num);
        }
    }

    Polygon(std::initializer_list<Point> init)
    : Polygon(std::vector<Point>(std::begin(init), std::end(init))) {}

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
        return init == ccw(_points[_num-2],
                           _points[_num-1],
                           _points[0]);
    }
    
    Point& operator[](size_t _n) {
        assert(_n < _num);
        return _points[_n];
    }

    const Point& operator[](size_t _n) const {
        assert(_n < _num);
        return _points[_n];
    }

    size_t size() const noexcept {
        return _num;
    }
    
    PolygonIterator begin() const;

    PolygonIterator end() const;

    friend PolygonIterator;

    private:
    // number of vertex
    const size_t _num;
    // list of vertexes
    // the order is counter-clockwise
    std::shared_ptr<Point[]> _points;
};

class PolygonIterator {
    public:
    using size_type         = std::size_t;
    using diff_type         = std::ptrdiff_t;
    using value_type        = Point;
    using refernce          = Point&;
    using pointer           = std::shared_ptr<Point[]>;
    using iterator_category = std::random_access_iterator_tag;

    refernce operator*() {
        return _ptr[_idx];
    }

    const refernce operator*() const {
        return _ptr[_idx];
    }

    PolygonIterator& operator++() {
        ++_idx;
        if(_idx == _length) _idx = 0;
        assert(check_idx());
        return *this;
    }

    PolygonIterator operator++(int) {
        auto ret = *this;
        ++*this;
        return ret;
    }

    PolygonIterator& operator--() {
        if(_idx == 0) _idx = _length;
        --_idx;
        assert(check_idx());
        return *this;
    }

    PolygonIterator operator--(int) {
        auto ret = *this;
        --*this;
        return ret;
    }

    PolygonIterator& operator+=(diff_type _n) {
        if(_n < 0) _n = _n % _length + _length;
        _idx += _n;
        if(_length <= _idx) _idx -= _length;
        assert(check_idx());
        return *this;
    }

    PolygonIterator  operator+(diff_type _n) const {
        auto ret = *this;
        ret += _n;
        return ret;
    }

    PolygonIterator& operator-=(diff_type _n) {
        return operator+=(-_n);
    }

    PolygonIterator  operator-(diff_type _n) const {
        auto ret = *this;
        ret -= _n;
        return ret;
    }

    size_type operator- (const PolygonIterator &i) const {
        auto ret = _idx - i._idx;
        return ret < 0 ? ret + _length : ret;
    }

    bool operator==(const PolygonIterator &i) const noexcept {
        return _ptr == i._ptr;
    }

    bool operator!=(const PolygonIterator &i) const noexcept {
        return !(*this == i);
    }

    friend Polygon;

    private:
    size_type _idx;
    const size_type _length;
    pointer _ptr;

    PolygonIterator(const Polygon *_parent, size_type _n = 0)
    : _idx(_n),
      _length(_parent->_num),
      _ptr(_parent->_points.get() + _n) {
        assert(check_idx());
    }

    bool check_idx() const noexcept {
        return _idx <= _length;
    }
};

PolygonIterator operator+(PolygonIterator::diff_type _n,
                          const PolygonIterator& _p) {
    return _p + _n;
}

PolygonIterator operator-(PolygonIterator::diff_type _n,
                          const PolygonIterator& _p) {
    return _p - _n;
}

PolygonIterator Polygon::begin() const {
        return PolygonIterator(this);
}

PolygonIterator Polygon::begin() const {
        return PolygonIterator(this);
}

} // namespace geometry

} // namespace sapphre15

#endif // GEOMETRY_POLYGON_HPP_
