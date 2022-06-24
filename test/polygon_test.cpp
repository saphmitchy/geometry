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

TEST(polygonTest, outsideTest) {
    Polygon pl = {Point(5.0, 2.0),
                  Point(4.0, -1.0),
                  Point(1.0, -2.0),
                  Point(-1.0, 1.0),
                  Point(-3.0, -3.0),
                  Point(-5.0, 2.0),
                  Point(0.0, 5.0)};
    EXPECT_TRUE(pl.outside(Point(-1.0, -2.0)));
    EXPECT_FALSE(pl.outside(Point(0.0, 0.0)));
}

TEST(polygonTest, issimpleTest) {
    auto rotate = [](std::vector<Point> v) {
        v.emplace_back(v[0]);
        std::copy(begin(v) + 1, end(v), begin(v));
        v.resize(v.size() - 1);
        return v;
    };
    std::vector<Point> buff = {Point(5.0, 2.0),
                               Point(8.0, 2.0),
                               Point(4.0, 3.0),
                               Point(2.0, 4.0),
                               Point(1.0, -3.0),
                               Point(-2.0, 0.0)};
    Polygon pl1(buff);
    EXPECT_FALSE(pl1.is_simple());
    buff = rotate(buff);
    Polygon pl2(buff);
    EXPECT_FALSE(pl2.is_simple());
    buff = rotate(buff);
    Polygon pl3(buff);
    EXPECT_FALSE(pl3.is_simple());
    buff = rotate(buff);
    Polygon pl4(buff);
    EXPECT_FALSE(pl4.is_simple());
    buff = rotate(buff);
    Polygon pl5(buff);
    EXPECT_FALSE(pl5.is_simple());
    buff = rotate(buff);
    Polygon pl6(buff);
    EXPECT_FALSE(pl6.is_simple());
    buff = rotate(buff);
    std::swap(buff[4], buff[5]);
    Polygon pl7(buff);
    EXPECT_TRUE(pl7.is_simple());
    buff = rotate(buff);
    Polygon pl8(buff);
    EXPECT_TRUE(pl8.is_simple());
    buff = rotate(buff);
    Polygon pl9(buff);
    EXPECT_TRUE(pl9.is_simple());
    buff = rotate(buff);
    Polygon pl10(buff);
    EXPECT_TRUE(pl10.is_simple());
    buff = rotate(buff);
    Polygon pl11(buff);
    EXPECT_TRUE(pl11.is_simple());
    buff = rotate(buff);
    Polygon pl12(buff);
    EXPECT_TRUE(pl12.is_simple());
}
