#include <cmath>

#include <config.hpp>
#include <line.hpp>

#include <gtest/gtest.h>

using namespace std;

using namespace sapphre15::geometry;

TEST(lineTest, onLineTest) {
    Line l0;
    EXPECT_TRUE(l0.on_line(Point(0.5, 0.5)));
    EXPECT_TRUE(l0.on_line(Point(-3.0, 4.0)));
    EXPECT_TRUE(l0.on_line(Point(3.0, -2.0)));
    EXPECT_FALSE(l0.on_line(Point(3.0, -2.5)));
    EXPECT_FALSE(l0.on_line(Point(10.0, -2.5)));
    Line l1(Point(4.0, 0.0), Point(2.0, 8.0));
    EXPECT_TRUE(l1.on_line(Point(0.5, 14.0)));
    EXPECT_TRUE(l1.on_line(Point(5.0, -4.0)));
    EXPECT_TRUE(l1.on_line(Point(-1.2, 20.8)));
    EXPECT_FALSE(l1.on_line(Point(3.0, -2.5)));
    EXPECT_FALSE(l1.on_line(Point(10.0, -2.5)));
    Line l2(Point(4.0, 0.0), Point(4.0, 8.0));
    EXPECT_TRUE(l2.on_line(Point(4.0, 0.0)));
    EXPECT_TRUE(l2.on_line(Point(4.0, -4.0)));
    EXPECT_TRUE(l2.on_line(Point(4.0, 20.8)));
    EXPECT_FALSE(l2.on_line(Point(3.0, -2.5)));
    EXPECT_FALSE(l2.on_line(Point(10.0, -2.5)));
    Line l3(Point(-2.0, 8.0), Point(4.0, 8.0));
    EXPECT_TRUE(l3.on_line(Point(-9.0, 8.0)));
    EXPECT_TRUE(l3.on_line(Point(0.0, 8.0)));
    EXPECT_TRUE(l3.on_line(Point(4.0, 8.0)));
    EXPECT_FALSE(l3.on_line(Point(3.0, -2.5)));
    EXPECT_FALSE(l3.on_line(Point(10.0, 7.9)));
}

TEST(lineTest, directionTest) {
    Line l1(Point(6.0, -6.0), Point(9.0, -2.0)),
         l2(Point(0.0, 0.0),  Point(2.0,  2.0));
    EXPECT_TRUE(l1.direction() == Point(0.6, 0.8));
    EXPECT_TRUE(l2.direction() == Point(1/sqrt(2), 1/sqrt(2)));
}

TEST(lineTest, onObjectTest) {
    Line l(5.0, 4.0, 2.0);
    EXPECT_TRUE(l.on_object(Point(-2.0, 2.0)));
    EXPECT_TRUE(l.on_object(Point(1.0, -1.75)));
    EXPECT_FALSE(l.on_object(Point(-2.0, 2.1)));
}

TEST(lineTest, coefficientConstructorTest) {
    Line l1(3.0, 4.0, -10.0);
    EXPECT_TRUE(l1.on_line(Point(2.0, 1.0)));
    EXPECT_TRUE(l1.on_line(Point(-2.0, 4.0)));
    EXPECT_FALSE(l1.on_line(Point(3.0, 4.0)));
    Line l2(0.0, 2.0, -4.0);
    EXPECT_TRUE(l2.on_line(Point(5.0, 2.0)));
    EXPECT_TRUE(l2.on_line(Point(-2.0, 2.0)));
    EXPECT_FALSE(l2.on_line(Point(3.0, 4.0)));
    Line l3(1.0, 0.0, 0.0);
    EXPECT_TRUE(l3.on_line(Point(0.0, 5.0)));
    EXPECT_TRUE(l3.on_line(Point(0.0, -2.0)));
    EXPECT_FALSE(l3.on_line(Point(3.0, 4.0)));
}

TEST(lineTest, directionConstructorTest) {
    Line l1(Point(1.0, 1.0), PI/4);
    EXPECT_TRUE(l1.on_line(Point(2.0, 2.0)));
    EXPECT_TRUE(l1.on_line(Point(-1.0, -1.0)));
    EXPECT_FALSE(l1.on_line(Point(-1.1, -1.0)));
    Line l2(Point(5.0, 1.0), 0.0);
    EXPECT_TRUE(l2.on_line(Point(5.0, 1.0)));
    EXPECT_TRUE(l2.on_line(Point(-9.0, 1.0)));
    EXPECT_FALSE(l2.on_line(Point(-5.0, -1.0)));
    Line l3(Point(-4.0, -1.0), -PI/2);
    EXPECT_TRUE(l3.on_line(Point(-4.0, 0.0)));
    EXPECT_TRUE(l3.on_line(Point(-4.0, -2.0)));
    EXPECT_FALSE(l3.on_line(Point(3.0, -1.0)));
}

TEST(lineTest, angleTest) {
    Line l1(Point(3, 4), Point(5, 6)),
         l2(Point(-8, 5), Point(-8, 9)),
         l3(Point(0, 4), Point(-sqrt(3), 5)),
         l4(Point(1.0, -9.0), Point(-1.0, -7.0));
    EXPECT_DOUBLE_EQ(angle(l1, l2), PI/4);
    EXPECT_DOUBLE_EQ(angle(l3, l1), PI*5/12);
    EXPECT_DOUBLE_EQ(angle(l3, l2), PI/3);
    EXPECT_DOUBLE_EQ(angle(l1, l4), PI/2);
    EXPECT_DOUBLE_EQ(angle(l4, l2), PI/4);
    EXPECT_DOUBLE_EQ(angle(l3, l4), PI/12);
}

TEST(lineTest, slopeTest) {
    Line l1(Point(3.0, 4.0), Point(-3.0, 7.0)),
         l2(Point(2.0, -1.0), Point(5.0, 6.0)),
         l3(Point(5.0, 3.0), Point(5.0, 2.0)),
         l4(Point(3.0, -1.0), Point(5.0, -1.0));
    EXPECT_DOUBLE_EQ(l1.slope(), -0.5);
    EXPECT_DOUBLE_EQ(l2.slope(), 7.0/3.0);
    EXPECT_DOUBLE_EQ(l3.slope(), INFINITY);
    EXPECT_DOUBLE_EQ(l4.slope(), 0.0);
}

TEST(lineTest, horizontalTest) {
    Line l1(Point(3.0, -1.0), Point(5.0, -1.0)),
         l2(Point(5.0, 3.0), Point(5.0, 2.0)),
         l3(Point(3.0, 4.0), Point(-3.0, 7.0));
    EXPECT_TRUE(l1.is_horizontal());
    EXPECT_FALSE(l2.is_horizontal());
    EXPECT_FALSE(l3.is_horizontal());
}

TEST(lineTest, verticalTest) {
    Line l1(Point(5.0, 3.0), Point(5.0, 2.0)),
         l2(Point(3.0, -1.0), Point(5.0, -1.0)),
         l3(Point(3.0, 4.0), Point(-3.0, 7.0));
    EXPECT_TRUE(l1.is_vertical());
    EXPECT_FALSE(l2.is_vertical());
    EXPECT_FALSE(l3.is_vertical());
}