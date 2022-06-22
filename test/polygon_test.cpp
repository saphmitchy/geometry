#include <config.hpp>
#include <polygon.hpp>
#include <vector>

#include <gtest/gtest.h>

using namespace sapphre15::geometry;

TEST(polygonTest, constructorTest) {
    Polygon pl1 = {Point(0.0, 1.0),
                   Point(1.0, 1.0),
                   Point(1.0, 0.0)},
            pl2 = {Point(1.0, 0.0),
                   Point(1.0, 1.0),
                   Point(0.0, 1.0)};
    EXPECT_TRUE(pl1[0] == Point(1.0, 0.0));
    EXPECT_TRUE(pl1[1] == Point(1.0, 1.0));
    EXPECT_TRUE(pl1[2] == Point(0.0, 1.0));
    EXPECT_TRUE(pl2[0] == Point(1.0, 0.0));
    EXPECT_TRUE(pl2[1] == Point(1.0, 1.0));
    EXPECT_TRUE(pl2[2] == Point(0.0, 1.0));
}

TEST(polygonTest, onObjectTest) {
    Polygon pl = {Point(0.0, 1.0),
                  Point(1.0, 1.0),
                  Point(1.0, 0.0)};
    EXPECT_TRUE(pl.on_object(Point(0.5, 0.5)));
    EXPECT_TRUE(pl.on_object(Point(1.0, 0.0)));
    EXPECT_TRUE(pl.on_object(Point(1.0, 0.1)));
    EXPECT_TRUE(pl.on_object(Point(0.2, 1.0)));
    EXPECT_FALSE(pl.on_object(Point(1.0, 1.1)));
    EXPECT_FALSE(pl.on_object(Point(-0.1, 1.1)));
    EXPECT_FALSE(pl.on_object(Point(0.7, 0.8)));
    EXPECT_FALSE(pl.on_object(Point(1.7, 0.8)));
}

TEST(polygonTest, areaTest) {
    Polygon pl1 = {Point(0.0, 1.0),
                   Point(1.0, 1.0),
                   Point(1.0, 0.0)},
            pl2 = {Point(5.0, 2.0),
                   Point(4.0, -1.0),
                   Point(1.0, -2.0),
                   Point(-1.0, 1.0),
                   Point(-3.0, -3.0),
                   Point(-5.0, 2.0),
                   Point(0.0, 5.0)};
    EXPECT_DOUBLE_EQ(pl1.area(), 0.5);
    EXPECT_DOUBLE_EQ(pl2.area(), 43.0);
}

TEST(polygonTest, insideTest) {
    Polygon pl = {Point(5.0, 2.0),
                   Point(4.0, -1.0),
                   Point(1.0, -2.0),
                   Point(-1.0, 1.0),
                   Point(-3.0, -3.0),
                   Point(-5.0, 2.0),
                   Point(0.0, 5.0)};
    EXPECT_TRUE(pl.inside(Point(0.0, 0.0)));
    EXPECT_TRUE(pl.inside(Point(-3.0, -2.0)));
    EXPECT_TRUE(pl.inside(Point(-3.0, -1.0)));
    EXPECT_TRUE(pl.inside(Point(-1.0, 4.0)));
    EXPECT_TRUE(pl.inside(Point(0.0, 2.0)));
    EXPECT_FALSE(pl.inside(Point(-1.0, 0.0)));
    EXPECT_FALSE(pl.inside(Point(-4.0, -5.0)));
    EXPECT_FALSE(pl.inside(Point(5.0, 1.0)));
    EXPECT_FALSE(pl.inside(Point(-7.0, 2.0)));
    EXPECT_FALSE(pl.inside(Point(-1.0, -2.0)));
}
