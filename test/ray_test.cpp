#include <gtest/gtest.h>

#include <config.hpp>
#include <ray.hpp>

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
    Ray ry1(Point(3.0, 0.0), PI * 3 / 4), ry2(Point(2.0, -1.0), -PI / 2),
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
    Ray ry1(Point(3.0, 0.0), PI * 3 / 4), ry2(Point(2.0, -1.0), -PI / 2),
        ry3(Point(-3.0, -5.0), Point(3.0, 5.0));
    EXPECT_TRUE(ry1.source() == Point(3.0, 0.0));
    EXPECT_TRUE(ry2.source() == Point(2.0, -1.0));
    EXPECT_TRUE(ry3.source() == Point(-3.0, -5.0));
}

TEST(rayTest, xTest) {
    Ray ry1(Point(3.0, 0.0), PI * 3 / 4), ry2(Point(2.0, -1.0), -PI / 2),
        ry3(Point(-3.0, -5.0), Point(3.0, 5.0));
    EXPECT_EQ(ry1.x(), 3.0);
    EXPECT_EQ(ry2.x(), 2.0);
    EXPECT_EQ(ry3.x(), -3.0);
}

TEST(rayTest, yTest) {
    Ray ry1(Point(3.0, 0.0), PI * 3 / 4), ry2(Point(2.0, -1.0), -PI / 2),
        ry3(Point(-3.0, -5.0), Point(3.0, 5.0));
    EXPECT_EQ(ry1.y(), 0.0);
    EXPECT_EQ(ry2.y(), -1.0);
    EXPECT_EQ(ry3.y(), -5.0);
}

TEST(RayTest, translationTest) {
    Ray r(Point(3.0, 4.0), Point(-1.0, 0.0));
    Ray r1 = r.translation(Point(-2.0, 5.0)),
        r2 = r.translation(Point(0.0, 0.0));
    EXPECT_DOUBLE_EQ(r1.x(), 1.0);
    EXPECT_DOUBLE_EQ(r1.y(), 9.0);
    EXPECT_DOUBLE_EQ(r1.slope(), r.slope());
    EXPECT_DOUBLE_EQ(r2.x(), 3.0);
    EXPECT_DOUBLE_EQ(r2.y(), 4.0);
    EXPECT_DOUBLE_EQ(r2.slope(), r.slope());
}

TEST(RayTest, moveXTest) {
    Ray r(Point(3.0, 4.0), Point(-1.0, 0.0));
    Ray r1 = r.moveX(4.0), r2 = r.moveX(0.0);
    EXPECT_DOUBLE_EQ(r1.x(), 7.0);
    EXPECT_DOUBLE_EQ(r1.y(), 4.0);
    EXPECT_DOUBLE_EQ(r1.slope(), r.slope());
    EXPECT_DOUBLE_EQ(r2.x(), 3.0);
    EXPECT_DOUBLE_EQ(r2.y(), 4.0);
    EXPECT_DOUBLE_EQ(r2.slope(), r.slope());
}

TEST(RayTest, moveYTest) {
    Ray r(Point(3.0, 4.0), Point(-1.0, 0.0));
    Ray r1 = r.moveY(-4.0), r2 = r.moveY(0.0);
    EXPECT_DOUBLE_EQ(r1.x(), 3.0);
    EXPECT_DOUBLE_EQ(r1.y(), 0.0);
    EXPECT_DOUBLE_EQ(r1.slope(), r.slope());
    EXPECT_DOUBLE_EQ(r2.x(), 3.0);
    EXPECT_DOUBLE_EQ(r2.y(), 4.0);
    EXPECT_DOUBLE_EQ(r2.slope(), r.slope());
}

TEST(RayTest, moveVTest) {
    Ray r(Point(2.0, 4.0), Point(-1.0, 0.0));
    Ray r1 = r.moveV(1.0), r2 = r.moveV(-2.0), r3 = r.moveV(0.0);
    EXPECT_DOUBLE_EQ(r1.x(), 2.8);
    EXPECT_DOUBLE_EQ(r1.y(), 3.4);
    EXPECT_DOUBLE_EQ(r1.slope(), r.slope());
    EXPECT_DOUBLE_EQ(r2.x(), 0.4);
    EXPECT_DOUBLE_EQ(r2.y(), 5.2);
    EXPECT_DOUBLE_EQ(r2.slope(), r.slope());
    EXPECT_DOUBLE_EQ(r3.x(), 2.0);
    EXPECT_DOUBLE_EQ(r3.y(), 4.0);
    EXPECT_DOUBLE_EQ(r3.slope(), r.slope());
}

TEST(RayTest, rotateTest) {
    Ray r(Point(3.0, 4.0), Point(-1.0, 0.0));
    Ray r1 = r.rotate(PI / 2), r2 = r.rotate(-PI * 3 / 4), r3 = r.rotate(0.0);
    EXPECT_DOUBLE_EQ(r1.x(), 3.0);
    EXPECT_DOUBLE_EQ(r1.y(), 4.0);
    EXPECT_DOUBLE_EQ(r1.slope(), -1.0);
    EXPECT_DOUBLE_EQ(r2.x(), 3.0);
    EXPECT_DOUBLE_EQ(r2.y(), 4.0);
    EXPECT_NEAR(r2.direction().x(), 0.0, 1e-15);
    EXPECT_DOUBLE_EQ(r2.direction().y(), 1.0);
    EXPECT_DOUBLE_EQ(r3.x(), 3.0);
    EXPECT_DOUBLE_EQ(r3.y(), 4.0);
    EXPECT_DOUBLE_EQ(r3.slope(), r.slope());
}