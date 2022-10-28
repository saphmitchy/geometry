#include <gtest/gtest.h>

#include <circle.hpp>

using namespace sapphre15::geometry;

TEST(circleTest, onObjectTest) {
    Circle c;
    EXPECT_TRUE(c.on_object(Point(-1.0, 0.0)));
    EXPECT_TRUE(c.on_object(Point(0.6, -0.8)));
    EXPECT_FALSE(c.on_object(Point(0.9, 0.4)));
}

TEST(circleTest, paramConstructorTest) {
    Circle c1(Point(0.5, -3.0), 4.0), c2(Point(0.0, 0.0), 1.0);
    EXPECT_TRUE(c1.on_object(Point(4.5, -3.0)));
    EXPECT_TRUE(c1.on_object(Point(0.5, 1.0)));
    EXPECT_FALSE(c1.on_object(Point(2.9, -0.8)));
    EXPECT_TRUE(c2.on_object(Point(-1.0, 0.0)));
    EXPECT_TRUE(c2.on_object(Point(0.6, -0.8)));
    EXPECT_FALSE(c2.on_object(Point(0.9, 0.4)));
}

TEST(circleTest, point2ConstructorTest) {
    Circle c(Point(3.0, -5.0), Point(3.7, -4.4));
    EXPECT_TRUE(c.on_object(Point(2.1, -5.2)));
    EXPECT_TRUE(c.on_object(Point(2.3, -4.4)));
    EXPECT_FALSE(c.on_object(Point(2.1, -5.1)));
}

TEST(circleTest, centerTest) {
    Circle c1(Point(-2.0, 5.0), 4.0);
    Circle c2(Point(3.0, -6.0), Point(100.0, 3.0));
    EXPECT_TRUE(c1.center() == Point(-2.0, 5.0));
    EXPECT_TRUE(c2.center() == Point(3.0, -6.0));
}

TEST(circleTest, radiusTest) {
    Circle c1(Point(-2.0, 5.0), 4.0);
    Circle c2(Point(3.0, -6.0), Point(100.0, 3.0));
    EXPECT_DOUBLE_EQ(c1.radius(), 4.0);
    EXPECT_DOUBLE_EQ(c2.radius(), sqrt(9490));
}

TEST(circleTest, insideTest) {
    Circle c(Point(-2.0, 5.0), 4.0);
    EXPECT_TRUE(c.inside(Point(0.5, 2.5)));
    EXPECT_TRUE(c.inside(Point(-5.0, 7.6)));
    EXPECT_TRUE(c.inside(Point(2.0, 5.0)));
    EXPECT_FALSE(c.inside(Point(0.0, .58)));
}

TEST(circleTest, outsideTest) {
    Circle c(Point(-2.0, 5.0), 4.0);
    EXPECT_TRUE(c.outside(Point(0.0, .58)));
    EXPECT_TRUE(c.outside(Point(1.0, 2.0)));
    EXPECT_FALSE(c.outside(Point(-5.0, 7.6)));
    EXPECT_FALSE(c.outside(Point(2.0, 5.0)));
}

TEST(circleTest, point3ConstructorTest) {
    Circle c1(
        Point(4855.0, -29.0), Point(-2406.0, 4218.0), Point(-1095.0, -4729.0)),
        c2(Point(-2.0, 1.0), Point(-2.0, -3.0), Point(0.0, -1.0));
    EXPECT_TRUE(c1.center() == Point(0.0, 1.0));
    EXPECT_DOUBLE_EQ(c1.radius(), sqrt(23571925.0));
    EXPECT_TRUE(c2.center() == Point(-2.0, -1.0));
    EXPECT_DOUBLE_EQ(c2.radius(), 2.0);
}

TEST(circleTest, incircleTest) {
    Circle c1 = incircle(Point(0.0, 0.0), Point(0.0, -3.0), Point(4.0, 0.0)),
           c2 = incircle(Point(-4.0, -59),
                         Point(13.0 / 3.0, 23.0 / 3.0),
                         Point(-17.0, 45.0));
    EXPECT_TRUE(c1.center() == Point(1.0, -1.0));
    EXPECT_DOUBLE_EQ(c1.radius(), 1.0);
    EXPECT_TRUE(c2.center() == Point(-4.0, 6.0));
    EXPECT_DOUBLE_EQ(c2.radius(), sqrt(65.0));
}