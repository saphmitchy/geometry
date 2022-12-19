#include <gtest/gtest.h>

#include <circle.hpp>
#include <tangent.hpp>

using namespace sapphre15::geometry;

TEST(tangentTest, CircleAndPoint) {
    Circle c1(Point(4.0, -2.0), 5.0), c2(Point(-1.0, 1.0), 3.0);
    Point  p1(9.0, 3.0), p2(-4.0, -7.0), p3(1.0, 2.0);
    auto   v11 = tangent(c1, p1), v12 = tangent(c1, p2), v13 = tangent(c1, p3),
         v21 = tangent(c2, p1), v22 = tangent(c2, p2), v23 = tangent(c2, p3);
    EXPECT_EQ(v11.size(), 2);
    EXPECT_DOUBLE_EQ(v11[0].x(), 9.0);
    EXPECT_DOUBLE_EQ(v11[0].y(), -2.0);
    EXPECT_DOUBLE_EQ(v11[1].x(), 4.0);
    EXPECT_DOUBLE_EQ(v11[1].y(), 3.0);
    EXPECT_EQ(v12.size(), 2);
    EXPECT_DOUBLE_EQ(v12[0].x(), -44.0/89.0);
    EXPECT_DOUBLE_EQ(v12[0].y(), 17.0/89.0);
    EXPECT_DOUBLE_EQ(v12[1].x(), 4.0);
    EXPECT_DOUBLE_EQ(v12[1].y(), -7.0);
    EXPECT_EQ(v13.size(), 1);
    EXPECT_DOUBLE_EQ(v13[0].x(), 1.0);
    EXPECT_DOUBLE_EQ(v13[0].y(), 2.0);
    EXPECT_EQ(v21.size(), 2);
    // EXPECT_DOUBLE_EQ(v21[0].x(), 0.42769967373897888052169946604);
    EXPECT_DOUBLE_EQ(v21[0].y(), -1.6384983686948935144300776301);
    EXPECT_DOUBLE_EQ(v21[1].x(), -0.69693044296974793194721087275);
    EXPECT_DOUBLE_EQ(v21[1].y(), 3.98465221484873977075835682626);
    EXPECT_EQ(v22.size(), 2);
    EXPECT_DOUBLE_EQ(v22[0].x(), -4.0);
    EXPECT_DOUBLE_EQ(v22[0].y(), 1.0);
    EXPECT_DOUBLE_EQ(v22[1].x(), 92.0 / 73.0);
    EXPECT_DOUBLE_EQ(v22[1].y(), -71.0 / 73.0);
    EXPECT_EQ(v23.size(), 0);
}
