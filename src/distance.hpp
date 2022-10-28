#ifndef GEOMETRY_DISTANCE_HPP_
#define GEOMETRY_DISTANCE_HPP_

#include <algorithm>
#include <type_traits>
#include <utility>

#include "config.hpp"
#include "intersection.hpp"
#include "line.hpp"
#include "point.hpp"
#include "segment.hpp"

namespace sapphre15 {

namespace geometry {

Real distance(const Line &l1, const Line &l2) {
    return parallel(l1, l2) ? distance(l1, l2._a) : 0;
}

Real distance(const Segment &l, const Point &p) {
    auto dd = dot(p - l.start(), l.end() - l.start());
    if (0 <= dd && dd <= norm(l.end() - l.start())) {
        return distance((Line)l, p);
    } else {
        return std::min(distance(l.start(), p), distance(l.end(), p));
    }
}

Real distance(const Point &p, const Segment &l) {
    return distance(l, p);
}

Real distance(const Segment &l1, const Line &l2) {
    if (intersection(l1, l2)) {
        return 0;
    } else {
        return std::min(distance(l2, l1.start()), distance(l2, l1.end()));
    }
}

Real distance(const Line &l1, const Segment &l2) {
    return distance(l2, l1);
}

// verified with
// https://onlinejudge.u-aizu.ac.jp/courses/library/4/CGL/2/CGL_2_D
Real distance(const Segment &l1, const Segment &l2) {
    if (intersection(l1, l2))
        return 0.0;
    else
        return std::min({distance(l1, l2.start()),
                         distance(l1, l2.end()),
                         distance(l2, l1.start()),
                         distance(l2, l1.end())});
}

Real distance(const Circle &c, const Line &l) {
    Real d = distance(c.center(), l);
    return std::max(d - c.radius(), 0.0);
    /**
     * This implementation calculates more accurately
     * especially when the circle's radius and
     * distance between the center and the line are near.
     * Because it consumes much time, I don't adopt it now.
     *
     *  if(intersection(c, l) != IntersectionCL::NOT_CROSS) return 0.0;
     *  else {
     *      Point d   = rotate(l.direction(), PI/2),
     *            nc1 = c.center() + d * c.radius(),
     *            nc2 = c.center() - d * c.radius();
     *      return std::min(distance(nc1, l), distance(nc2, l));
     *  }
     */
}

Real distance(const Line &l, const Circle &c) {
    return distance(c, l);
}

}  // namespace geometry

}  // namespace sapphre15

#endif  // GEOMETRY_DISTANCE_HPP_