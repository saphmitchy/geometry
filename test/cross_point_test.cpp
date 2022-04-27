#include <vector>

#include <config.hpp>
#include <line.hpp>
#include <segment.hpp>
#include <cross_point.hpp>

#include <gtest/gtest.h>

using namespace std;

using namespace sapphre15::geometry;

TEST(crossPointTest, LineAndLineTest) {
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

TEST(crossPointTest, SegmentAndLineTest) {
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

TEST(crossPointTest, LineAndSegmentTest) {
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

TEST(crossPointTest, SegmentAndSegmentTest) {
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

TEST(crossPointTest, CircleAndLineTest) {
    Circle c1(Point(3.0, -1.0), 5.0),
           c2(Point(0.0, -2.0), 1.0),
           c3(Point(-12.0, 1.0), 10.0);
    Line l1(3.0, -4.0, 12.0),
         l2(1.0, 0.0, 1.0);
    auto v11 = cross_point(c1, l1),
         v12 = cross_point(c1, l2),
         v21 = cross_point(c2, l1),
         v22 = cross_point(c2, l2),
         v31 = cross_point(c3, l1),
         v32 = cross_point(c3, l2);
    EXPECT_EQ(v11.size(), 1);
    EXPECT_DOUBLE_EQ(v11[0].x(), 0.0);
    EXPECT_DOUBLE_EQ(v11[0].y(), 3.0);
    EXPECT_EQ(v12.size(), 2);
    EXPECT_DOUBLE_EQ(v12[0].x(), -1.0);
    EXPECT_DOUBLE_EQ(v12[0].y(), 2.0);
    EXPECT_DOUBLE_EQ(v12[1].x(), -1.0);
    EXPECT_DOUBLE_EQ(v12[1].y(), -4.0);
    EXPECT_TRUE(v21.empty());
    EXPECT_EQ(v22.size(), 1);
    EXPECT_DOUBLE_EQ(v22[0].x(), -1.0);
    EXPECT_DOUBLE_EQ(v22[0].y(), -2.0);
    EXPECT_EQ(v31.size(), 2);
    EXPECT_DOUBLE_EQ(v31[0].x(), -2.012059143293446705769156324095);
    EXPECT_DOUBLE_EQ(v31[0].y(), 1.490955642529915081695435219444);
    EXPECT_DOUBLE_EQ(v31[1].x(), -15.267940856706553987010011042003);
    EXPECT_DOUBLE_EQ(v31[1].y(), -8.450955642529914157989878731314);
    EXPECT_TRUE(v32.empty());
}

TEST(crossPointTest, LineAndCircleTest) {
    Circle c1(Point(4.0, -1.0), 297.0);
    Line l1(128.0, 268.0, -88452.0);
    auto v11 = cross_point(c1, l1);
    EXPECT_EQ(v11.size(), 2);
    EXPECT_DOUBLE_EQ(v11[0].x(), 131.097637982719589899716083891690);
    EXPECT_DOUBLE_EQ(v11[0].y(), 267.430978873924971139786066487432);
    EXPECT_DOUBLE_EQ(v11[1].x(), 132.902362017280410100283916108310);
    EXPECT_DOUBLE_EQ(v11[1].y(), 266.569021126075028860213933512568);
}