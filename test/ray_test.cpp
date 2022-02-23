#include <config.hpp>
#include <ray.hpp>

#include <gtest/gtest.h>

using namespace std;

using namespace sapphre15::geometry;

TEST(rayTest, onObjectTest) {
    Ray ry;
    EXPECT_TRUE(ry.on_object(Point(-2.0, 3.0)));
    EXPECT_TRUE(ry.on_object(Point(1.0, 0.0)));
    EXPECT_TRUE(ry.on_object(Point(0.0, 1.0)));
    EXPECT_TRUE(ry.on_object(Point(0.5, 0.5)));
    EXPECT_FALSE(ry.on_object(Point(1.1, -0.1)));
    EXPECT_FALSE(ry.on_object(Point(1.2, 0.0)));
    EXPECT_FALSE(ry.on_object(Point(-4.0, 4.0)));
}

TEST(rayTest, endPointConstructorTest) {
    Ray ry1(Point(3.0, 4.0), Point(2.0, 5.0)),
        ry2(Point(0.0, 3.0), Point(-1.0, 3.0)),
        ry3(Point(0.0, 0.0), Point(0.0, 5.0));
    EXPECT_TRUE(ry1.on_object(Point(0.0, 7.0)));
    EXPECT_TRUE(ry1.on_object(Point(3.0, 4.0)));
    EXPECT_FALSE(ry1.on_object(Point(4.0, 3.0)));
    EXPECT_TRUE(ry2.on_object(Point(-0.5, 3.0)));
    EXPECT_TRUE(ry2.on_object(Point(-1.0, 3.0)));
    EXPECT_FALSE(ry2.on_object(Point(0.1, 3.0)));
    EXPECT_FALSE(ry2.on_object(Point(-1.0, 2.0)));
    EXPECT_TRUE(ry3.on_object(Point(0.0, 3.0)));
    EXPECT_FALSE(ry2.on_object(Point(0.0, -6.0)));
    EXPECT_FALSE(ry2.on_object(Point(-1.0, 2.0)));
}

TEST(rayTest, directionConstructorTest) {
    Ray ry1(Point(3.0, 0.0), PI*3 / 4),
        ry2(Point(2.0, -1.0), -PI/2),
        ry3(Point(-3.0, -5.0), -PI);
    EXPECT_TRUE(ry1.on_object(Point(0.0, 3.0)));
    EXPECT_TRUE(ry1.on_object(Point(2.5, 0.5)));
    EXPECT_FALSE(ry1.on_object(Point(4.0, -1.0)));
    EXPECT_TRUE(ry2.on_object(Point(2.0, -2.0)));
    EXPECT_TRUE(ry2.on_object(Point(2.0, -1.5)));
    EXPECT_FALSE(ry2.on_object(Point(4.0, -1.0)));
    EXPECT_TRUE(ry3.on_object(Point(-3.0, -5.0)));
    EXPECT_TRUE(ry3.on_object(Point(-5.0, -5.0)));
    EXPECT_FALSE(ry3.on_object(Point(4.0, -5.0)));
}

TEST(rayTest, sourceTest) {
    Ray ry1(Point(3.0, 0.0), PI*3 / 4),
        ry2(Point(2.0, -1.0), -PI/2),
        ry3(Point(-3.0, -5.0), Point(3.0, 5.0));
    EXPECT_TRUE(ry1.source() == Point(3.0, 0.0));
    EXPECT_TRUE(ry2.source() == Point(2.0, -1.0));
    EXPECT_TRUE(ry3.source() == Point(-3.0, -5.0));
}

TEST(rayTest, xTest) {
    Ray ry1(Point(3.0, 0.0), PI*3 / 4),
        ry2(Point(2.0, -1.0), -PI/2),
        ry3(Point(-3.0, -5.0), Point(3.0, 5.0));
    EXPECT_EQ(ry1.x(), 3.0);
    EXPECT_EQ(ry2.x(), 2.0);
    EXPECT_EQ(ry3.x(), -3.0);
}

TEST(rayTest, yTest) {
    Ray ry1(Point(3.0, 0.0), PI*3 / 4),
        ry2(Point(2.0, -1.0), -PI/2),
        ry3(Point(-3.0, -5.0), Point(3.0, 5.0));
    EXPECT_EQ(ry1.y(), 0.0);
    EXPECT_EQ(ry2.y(), -1.0);
    EXPECT_EQ(ry3.y(), -5.0);
}