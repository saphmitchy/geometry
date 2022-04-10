#include <vector>
#include <cmath>

#include <config.hpp>
#include <line.hpp>
#include <segment.hpp>
#include <distance.hpp>

#include <gtest/gtest.h>

using namespace std;

using namespace sapphre15::geometry;

TEST(distanceTest, LineAndPointTest) {
    Line l1(0, 3.0, 6.0),
         l2(-4.0, 0.0, 4.0),
         l3(4.0, 3.0, 6.0);
    Point p1(8.0, 0.0),
          p2(0.0, -5.0),
          p3(-3.0, 2.0);
    EXPECT_DOUBLE_EQ(distance(l1, p1), 2.0);
    EXPECT_DOUBLE_EQ(distance(l1, p2), 3.0);
    EXPECT_DOUBLE_EQ(distance(l1, p3), 4.0);
    EXPECT_DOUBLE_EQ(distance(l2, p1), 7.0);
    EXPECT_DOUBLE_EQ(distance(l2, p2), 1.0);
    EXPECT_DOUBLE_EQ(distance(l2, p3), 4.0);
    EXPECT_DOUBLE_EQ(distance(l3, p1), 7.6);
    EXPECT_DOUBLE_EQ(distance(l3, p2), 1.8);
    EXPECT_DOUBLE_EQ(distance(l3, p3), 0.0);
}

TEST(distanceTest, PointAndLineTest) {
    Line l1(5.0, 12.0, -6.0);
    Point p1(0.0, 0.0);
    EXPECT_DOUBLE_EQ(distance(p1, l1), 6.0/13.0);
}

TEST(distanceTest, LineAndLineTest) {
    Line l1(8.0, 6.0, 1.0),
         l2(-4.0, -3.0, 5.0),
         l3(2.0, 3.0, 6.0);
    EXPECT_DOUBLE_EQ(distance(l1, l2), 1.1);
    EXPECT_DOUBLE_EQ(distance(l3, l1), 0.0);
    EXPECT_DOUBLE_EQ(distance(l2, l3), 0.0);
}

TEST(distanceTest, SegmentAndPointTest) {
    Segment sg1(Point(6.0, -4.0), Point(-3.0, 8.0)),
            sg2(Point(-6.0, 3.0), Point(-2.0, 3.0)),
            sg3(Point(6.0, 2.0), Point(6.0, 9.0));
    Point p1(0.0, 0.0),
          p2(-6.0, 12.0),
          p3(46.0, 5.0);
    EXPECT_DOUBLE_EQ(distance(sg1, p1), 2.4);
    EXPECT_DOUBLE_EQ(distance(sg1, p2), 5.0);
    EXPECT_DOUBLE_EQ(distance(sg1, p3), 41.0);
    EXPECT_DOUBLE_EQ(distance(sg2, p1), sqrt(13.0));
    EXPECT_DOUBLE_EQ(distance(sg2, p2), 9.0);
    EXPECT_DOUBLE_EQ(distance(sg2, p3), sqrt(2308.0));
    EXPECT_DOUBLE_EQ(distance(sg3, p1), sqrt(40.0));
    EXPECT_DOUBLE_EQ(distance(sg3, p2), sqrt(153.0));
    EXPECT_DOUBLE_EQ(distance(sg3, p3), 40.0);
}

TEST(distanceTest, PointAndSegmentTest) {
    Segment sg1(Point(6.0, 0.0), Point(-3.0, 0.0));
    Point p1(0.0, 0.0), p2(-46.0, 0.0);
    EXPECT_DOUBLE_EQ(distance(sg1, p1), 0.0);
    EXPECT_DOUBLE_EQ(distance(sg1, p2), 43.0);
}

TEST(distanceTest, SegmentAndLineTest) {
    Segment sg1(Point(2.0, 4.0), Point(-1.0, 0.0)),
            sg2(Point(2.0, 4.0), Point(-2.0, 4.0)),
            sg3(Point(-1.0, 4.0), Point(-1.0, 3.0));
    Line l1(2.0, -1.0, 4.0);
    EXPECT_DOUBLE_EQ(distance(sg1, l1), sqrt(0.8));
    EXPECT_DOUBLE_EQ(distance(sg2, l1), sqrt(0.0));
    EXPECT_DOUBLE_EQ(distance(sg3, l1), sqrt(0.2));
}

TEST(distanceTest, LineAndSegmentTest) {
    Segment sg1(Point(2.0, 4.0), Point(-1.0, 0.0)),
            sg2(Point(2.0, 4.0), Point(-2.0, 4.0)),
            sg3(Point(-1.0, 4.0), Point(-1.0, 3.0));
    Line l1(2.0, -1.0, 4.0);
    EXPECT_DOUBLE_EQ(distance(sg1, l1), sqrt(0.8));
    EXPECT_DOUBLE_EQ(distance(sg2, l1), sqrt(0.0));
    EXPECT_DOUBLE_EQ(distance(sg3, l1), sqrt(0.2));
}