#ifndef GEOMETRY_POLYGON_HPP_
#define GEOMETRY_POLYGON_HPP_

#include <algorithm>
#include <initializer_list>
#include <iterator>
#include <memory>
#include <vector>

#include "config.hpp"
#include "intersection.hpp"
#include "point.hpp"
#include "segment.hpp"

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
    Polygon(const std::vector<Point>& points_list) : _num(points_list.size()) {
        assert(3 <= _num);
        _points.reset(new Point[_num]);
        std::copy(
            std::begin(points_list), std::end(points_list), _points.get());
        // the order is checked.
        if (sgn(area()) < 0) {
            std::reverse(_points.get(), _points.get() + _num);
        }
    }

    Polygon(std::initializer_list<Point> init)
        : Polygon(std::vector<Point>(std::begin(init), std::end(init))) {
    }

    /**
     * @brief calculate the area of the polygon.
     * veified with
     * https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/3/CGL_3_A
     * @return Real
     */
    Real area() const {
        Real val = cross(_points[_num - 1], _points[0]);
        for (size_t i = 0; i < _num - 1; i++) {
            val += cross(_points[i], _points[i + 1]);
        }
        return val / 2.0;
    }

    /**
     * @brief Check if the point is inside the polygon.
     * If the points is on the polygon, the result is unspecified.
     * veified with
     * https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/3/CGL_3_C
     * @param p Point
     */
    bool inside(const Point& p) {
        bool  ret = false;
        Point _a, _b = _points[_num - 1];
        for (size_t i = 0; i < _num; i++) {
            _a = std::move(_b);
            _b = _points[i];
            if (_a.y() < _b.y()) std::swap(_a, _b);
            if (!le(_a.y(), p.y()) && le(_b.y(), p.y()) &&
                ccw(_a, p, _b) == COUNTER_CLOCKWISE) {
                ret = ret ^ true;
            }
            _b = _points[i];
        }
        return ret;
    }
    /**
     * @brief Check if the point is on edges of the polygon.
     * @param p
     */
    bool on_object(const Point& p) {
        for (size_t i = 1; i < _num; i++) {
            if (ccw(_points[i - 1], _points[i], p) == ON_SEGMENT) {
                return true;
            }
        }
        return ccw(_points[0], _points[_num - 1], p) == ON_SEGMENT;
    }
    /**
     * @brief Check if the point is outside the polygon.
     * @param p Point
     */
    bool outside(const Point& p) {
        return !inside(p);
    }
    /**
     * @brief Check if the point is simple.
     * @param p Point
     */
    bool is_simple() {
        Point ip = _points[_num - 1];
        for (size_t i = 0; i < _num; i++) {
            for (size_t j = i + 1; j < (i == 0 ? _num - 2 : _num - 1); j++) {
                if (intersection(Segment(_points[i], ip),
                                 Segment(_points[j], _points[j + 1]))) {
                    return false;
                }
            }
            ip = _points[i];
        }
        return true;
    }
    /**
     * @brief Check if the polygon is convex.
     * veryfied with
     * https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/3/CGL_3_B
     */
    bool is_convex() {
        if (ccw(_points[_num - 1], _points[0], _points[1]) == CLOCKWISE)
            return false;
        if (ccw(_points[_num - 2], _points[_num - 1], _points[0]) == CLOCKWISE)
            return false;
        for (size_t i = 2; i < _num; i++) {
            if (ccw(_points[i - 2], _points[i - 1], _points[i]) == CLOCKWISE)
                return false;
        }
        return true;
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
        if (_idx == _length) _idx = 0;
        assert(check_idx());
        return *this;
    }

    PolygonIterator operator++(int) {
        auto ret = *this;
        ++*this;
        return ret;
    }

    PolygonIterator& operator--() {
        if (_idx == 0) _idx = _length;
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
        if (_n < 0) _n = _n % _length + _length;
        _idx += _n;
        if (_length <= _idx) _idx -= _length;
        assert(check_idx());
        return *this;
    }

    PolygonIterator operator+(diff_type _n) const {
        auto ret = *this;
        ret += _n;
        return ret;
    }

    PolygonIterator& operator-=(diff_type _n) {
        return operator+=(-_n);
    }

    PolygonIterator operator-(diff_type _n) const {
        auto ret = *this;
        ret -= _n;
        return ret;
    }

    size_type operator-(const PolygonIterator& i) const {
        auto ret = _idx - i._idx;
        return ret < 0 ? ret + _length : ret;
    }

    bool operator==(const PolygonIterator& i) const noexcept {
        return _ptr == i._ptr;
    }

    bool operator!=(const PolygonIterator& i) const noexcept {
        return !(*this == i);
    }

    Point* operator->() const noexcept {
        return &_ptr[_idx];
    }

    friend Polygon;

   private:
    size_type       _idx;
    const size_type _length;
    pointer         _ptr;

    PolygonIterator(const Polygon* _parent, size_type _n = 0)
        : _idx(_n), _length(_parent->_num), _ptr(_parent->_points) {
        assert(check_idx());
    }

    bool check_idx() const noexcept {
        return _idx <= _length;
    }
};

PolygonIterator operator+(PolygonIterator::diff_type _n,
                          const PolygonIterator&     _p) {
    return _p + _n;
}

PolygonIterator operator-(PolygonIterator::diff_type _n,
                          const PolygonIterator&     _p) {
    return _p - _n;
}

PolygonIterator Polygon::begin() const {
    return PolygonIterator(this);
}

PolygonIterator Polygon::end() const {
    return PolygonIterator(this);
}

}  // namespace geometry

}  // namespace sapphre15

#endif  // GEOMETRY_POLYGON_HPP_
