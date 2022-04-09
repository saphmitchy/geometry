#include <vector>

#include <config.hpp>
#include <line.hpp>
#include <segment.hpp>
#include <distance.hpp>

#include <gtest/gtest.h>

using namespace std;

using namespace sapphre15::geometry;

TEST(distanceTest, LineandPointTest) {
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

TEST(distanceTest, PointandLineTest) {
    Line l1(5.0, 12.0, -6.0);
    Point p1(0.0, 0.0);
    EXPECT_DOUBLE_EQ(distance(p1, l1), 6.0/13.0);
}


TEST(distanceTest, LineandLineTest) {
    Line l1(8.0, 6.0, 1.0),
         l2(-4.0, -3.0, 5.0),
         l3(2.0, 3.0, 6.0);
    EXPECT_DOUBLE_EQ(distance(l1, l2), 1.1);
    EXPECT_DOUBLE_EQ(distance(l3, l1), 0.0);
    EXPECT_DOUBLE_EQ(distance(l2, l3), 0.0);
}