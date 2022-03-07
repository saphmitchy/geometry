#include <vector>

#include <config.hpp>
#include <line.hpp>
#include <segment.hpp>
#include <cross_point.hpp>

#include <gtest/gtest.h>

using namespace std;

using namespace sapphre15::geometry;

TEST(crossPointTest, LineandLineTest) {
    Line l1(3.0, 4.0, 5.0),
         l2(-3.0, 2.0, 6.0),
         l3(0.0, 5.0, -3.0),
         l4(1.0, 0.0, -8.0);
    Point p1 = cross_point(l1, l2)[0],
          p2 = cross_point(l1, l3)[0],
          p3 = cross_point(l1, l4)[0],
          p4 = cross_point(l2, l3)[0],
          p5 = cross_point(l2, l4)[0],
          p6 = cross_point(l4, l3)[0];
    EXPECT_NEAR(p1.x(), 7.0/9.0, 1e-13);
    EXPECT_NEAR(p1.y(), -11.0/6.0, 1e-13);
    EXPECT_NEAR(p2.x(), -37.0/15.0, 1e-13);
    EXPECT_NEAR(p2.y(), 3.0/5.0, 1e-13);
    EXPECT_NEAR(p3.x(), 8.0, 1e-13);
    EXPECT_NEAR(p3.y(), -7.25, 1e-13);
    EXPECT_NEAR(p4.x(), 12.0/5.0, 1e-13);
    EXPECT_NEAR(p4.y(), 3.0/5.0, 1e-13);
    EXPECT_NEAR(p5.x(), 8.0, 1e-13);
    EXPECT_NEAR(p5.y(), 9.0, 1e-13);
    EXPECT_NEAR(p6.x(), 8.0, 1e-13);
    EXPECT_NEAR(p6.y(), 3.0/5.0, 1e-13);
}

TEST(crossPointTest, SegmentandLineTest) {
    Segment sg1(Point(3.0, -1.0), Point(6.0, 2.0)),
            sg2(Point(-1.0, 7.0), Point(2.0, -2.0));
    Line l1(Point(4.0, -3.0), Point(4.0, -9.0)),
         l2(Point(2.5, -1.5), Point(0, 3.5)),
         l3(Point(6.0, 2.0), Point(-1.0, 7.0));
    vector<Point> p1 = cross_point(sg1, l1),
                  p2 = cross_point(sg1, l2),
                  p3 = cross_point(sg1, l3),
                  p4 = cross_point(sg2, l1),
                  p5 = cross_point(sg2, l2),
                  p6 = cross_point(sg2, l3);
    EXPECT_NEAR(p1[0].x(), 4.0, 1e-13);
    EXPECT_NEAR(p1[0].y(), 0.0, 1e-13);
    EXPECT_TRUE(p2.empty());
    EXPECT_NEAR(p3[0].x(), 6.0, 1e-13);
    EXPECT_NEAR(p3[0].y(), 2.0, 1e-13);
    EXPECT_TRUE(p4.empty());
    EXPECT_NEAR(p5[0].x(), 0.5, 1e-13);
    EXPECT_NEAR(p5[0].y(), 2.5, 1e-13);
    EXPECT_NEAR(p6[0].x(), -1.0, 1e-13);
    EXPECT_NEAR(p6[0].y(), 7.0, 1e-13);
}

TEST(crossPointTest, LineandSegmentTest) {
    Line l1(Point(-4.0, -2.0), Point(5.0, 2.0)),
         l2(Point(-1.0, 3.0), Point(2.0, -2.0));
    Segment sg1(Point(-5.0, 0.0), Point(5.0, 0.0)),
            sg2(Point(-7.0, 4.0), Point(2.0, 2.5));
    vector<Point> p1 = cross_point(l1, sg1),
                  p2 = cross_point(l1, sg2),
                  p3 = cross_point(l2, sg1),
                  p4 = cross_point(l2, sg2);
    EXPECT_NEAR(p1[0].x(), 0.5, 1e-13);
    EXPECT_NEAR(p1[0].y(), 0.0, 1e-13);
    EXPECT_TRUE(p2.empty());
    EXPECT_NEAR(p3[0].x(), 0.8, 1e-13);
    EXPECT_NEAR(p3[0].y(), 0.0, 1e-13);
    EXPECT_NEAR(p4[0].x(), -1.0, 1e-13);
    EXPECT_NEAR(p4[0].y(), 3.0, 1e-13);
}

TEST(crossPointTest, SegmentandSegmentTest) {
    Segment sg1(Point(-1.0, 0.0), Point(0.0, 2.0)),
            sg2(Point(-3.0, 4.0), Point(2.0, -1.0)),
            sg3(Point(0.5, -0.5), Point(-4.0, 1.0));
    vector<Point> p1 = cross_point(sg1, sg2),
                  p2 = cross_point(sg2, sg3),
                  p3 = cross_point(sg3, sg1);
    EXPECT_NEAR(p1[0].x(), -1.0/3.0, 1e-13);
    EXPECT_NEAR(p1[0].y(), 4.0/3.0, 1e-13);
    EXPECT_TRUE(p2.empty());
    EXPECT_NEAR(p3[0].x(), -1.0, 1e-13);
    EXPECT_NEAR(p3[0].y(), 0.0, 1e-13);
}