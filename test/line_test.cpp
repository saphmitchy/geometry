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

TEST(lineTest, parameterizedConstructorTest) {
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