#include <cmath>

#include <config.hpp>
#include <point.hpp>
#include <line.hpp>
#include <intersection.hpp>

#include <gtest/gtest.h>

using namespace std;

using namespace sapphre15::geometry;

TEST(intersectionTest, LineAndLine) {
    Line l1(3.0, 4.0, 5.0),
         l2(-6.0, -8.0, 10.0),
         l3(5.0, 10.0, 0.0);
    EXPECT_FALSE(intersection(l1, l2));
    EXPECT_TRUE(intersection(l1, l3));
    EXPECT_TRUE(intersection(l2, l3));
}

TEST(intersectionTest, SegmentAndLine) {
    Line l1(3.0, -1.0, 5.0),
         l2(5.0, 10.0, 0.0);
    Segment sg1(Point(2.0, -1.0), Point(5.0, 5.0)),
            sg2(Point(-1.0, -3.0), Point(-1.0, 2.0)),
            sg3(Point(-2.0, -4.0), Point(6.0, -1.0)),
            sg4(Point(-2.0, 1.0), Point(4.0, -2.0));
    EXPECT_TRUE(intersection(l2, sg1));
    EXPECT_TRUE(intersection(l1, sg2));
    EXPECT_TRUE(intersection(l2, sg2));
    EXPECT_TRUE(intersection(l2, sg3));
    EXPECT_TRUE(intersection(l2, sg4));
    EXPECT_FALSE(intersection(l1, sg1));
    EXPECT_FALSE(intersection(l1, sg3));
}

TEST(intersectionTest, LineAndSegment) {
    Line l1(3.0, -1.0, 5.0);
    Segment sg1(Point(-2.0, 4.0), Point(5.0, 5.0)),
            sg2(Point(-2.0, -1.1), Point(6.0, -13.0));
    EXPECT_TRUE(intersection(sg1, l1));
    EXPECT_FALSE(intersection(sg2, l1));
}

TEST(intersectionTest, SegmentAndSegment1) {
    Segment sg1(Point(2.0, 4.0), Point(-3.0, -3.0)),
            sg2(Point(-3.0, -3.0), Point(5.0, 1.0)),
            sg3(Point(1.0, -1.0), Point(-3.0, 3.0)),
            sg4(Point(0.0, 1.0), Point(5.0, 1.0));
    EXPECT_TRUE(intersection(sg1, sg2));
    EXPECT_TRUE(intersection(sg1, sg3));
    EXPECT_TRUE(intersection(sg3, sg2));
    EXPECT_TRUE(intersection(sg2, sg4));
    EXPECT_FALSE(intersection(sg1, sg4));
    EXPECT_FALSE(intersection(sg3, sg4));
}

TEST(intersectionTest, SegmentAndSegmentSameLine) {
    Segment sg1(Point(0.0, 2.0), Point(-2.0, 0.0)),
            sg2(Point(-2.0, 0.0), Point(-10.0, -8.0)),
            sg3(Point(10.0, 8.0), Point(0.0, 2.0)),
            sg4(Point(4.0, 6.0), Point(-6.0, -4.0));
    EXPECT_TRUE(intersection(sg1, sg2));
    EXPECT_TRUE(intersection(sg1, sg3));
    EXPECT_TRUE(intersection(sg1, sg4));
    EXPECT_TRUE(intersection(sg2, sg4));
    EXPECT_TRUE(intersection(sg3, sg4));
    EXPECT_FALSE(intersection(sg3, sg2));
}
