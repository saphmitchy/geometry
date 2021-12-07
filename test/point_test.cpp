#include <point.hpp>

#include <gtest/gtest.h>

using namespace sapphre15::geometry;

TEST(pointTest, defaultConstructorTest) {
    Point p;
    EXPECT_EQ(p.x(), 0.0);
    EXPECT_EQ(p.y(), 0.0);
}

TEST(pointTest, parametarizedConstructorTest) {
    Point p(3.0, 2.0), q(-1, 0);
    EXPECT_EQ(p.x(), 3.0);
    EXPECT_EQ(p.y(), 2.0);
    EXPECT_EQ(q.x(), -1.0);
    EXPECT_EQ(q.y(), 0.0);
}

TEST(pointTest, assignXTest) {
    Point p(3.0, 2.0);
    p.x(-4.0);
    EXPECT_EQ(p.x(), -4.0);
    p.x(-PI * 2);
    EXPECT_EQ(p.x(), -PI * 2);
    EXPECT_EQ(p.y(), 2.0);
}

TEST(pointTest, assignYTest) {
    Point p(3.0, 2.0);
    p.y(-4.0);
    EXPECT_EQ(p.y(), -4.0);
    p.y(-PI * 2);
    EXPECT_EQ(p.y(), -PI * 2);
    EXPECT_EQ(p.x(), 3.0);
}

TEST(pointTest, eqTest) {
    Point p(3.0, 2.0), q(3.0, 2.0);
    EXPECT_TRUE(p == q);
    p = Point(3.00000000001, 1.9999999999999);
    EXPECT_TRUE(p == q);
    p = Point(400000000000, -100000);
    q = Point(400000000002, -100000.000001);
    EXPECT_TRUE(p == q);
    q = Point(400000000002, -100001);
    EXPECT_FALSE(p == q);
    q = Point(-400000000000, -100000.00001);
    EXPECT_FALSE(p == q);
    p = Point(3.00000000001, 1.9999999999999);
    EXPECT_FALSE(p == q);
}

TEST(pointTest, neqTest) {
    Point p(3.0, 2.0), q(4.0, 2.0);
    EXPECT_TRUE(p != q);
    p = Point(3.00000000001, 1.9999999999999);
    EXPECT_TRUE(p != q);
    p = Point(400000000000, -100000);
    q = Point(400000000002, -100000.00001);
    EXPECT_TRUE(p != q);
}

TEST(pointTest, addAssignTest) {
    Point p(3.0, 2.0), q(-5.7, PI);
    p += q;
    EXPECT_TRUE(p == Point(-2.7, 2.0 + PI));
    EXPECT_TRUE(q == Point(-5.7, PI));
    Point r(-3.0, 0.0), s(110.0, 4.5);
    r += s;
    EXPECT_TRUE(r == Point(107.0, 4.5));
    EXPECT_TRUE(s == Point(110.0, 4.5));
}

TEST(pointTest, minusAssignTest) {
    Point p(3.0, 2.0), q(-5.7, PI);
    p -= q;
    EXPECT_TRUE(p == Point(8.7, 2.0 - PI));
    EXPECT_TRUE(q == Point(-5.7, PI));
    Point r(3.0, 0.0), s(110.0, -4.5);
    r -= s;
    EXPECT_TRUE(r == Point(-107.0, 4.5));
    EXPECT_TRUE(s == Point(110.0, -4.5));
}

TEST(pointTest, productAssignTest1) {
    Point p(3.0, 2.0), q(-5.7, PI);
    p *= q;
    EXPECT_TRUE(p == Point(-17.1, 2.0 * PI));
    EXPECT_TRUE(q == Point(-5.7, PI));
    Point r(3.0, 0.0), s(110.0, -4.5);
    r *= s;
    EXPECT_TRUE(r == Point(330.0, 0.0));
    EXPECT_TRUE(s == Point(110.0, -4.5));
}

TEST(pointTest, productAssignTest2) {
    Point p(3.0, PI);
    Real q = -5.7;
    p *= q;
    EXPECT_TRUE(p == Point(-17.1, -5.7 * PI));
    EXPECT_TRUE(q == -5.7);
    Point r(3.0, 0.0);
    Real s = 110.0;
    r *= s;
    EXPECT_TRUE(r == Point(330.0, 0.0));
    EXPECT_TRUE(s == 110.0);
}

TEST(pointTest, divisionAssignTest1) {
    Point p(3.0, 2.0), q(-5.7, PI);
    p /= q;
    EXPECT_TRUE(p == Point(3.0 / -5.7, 2.0 / PI));
    EXPECT_TRUE(q == Point(-5.7, PI));
    Point r(3.0, 0.0), s(110.0, -4.5);
    r /= s;
    EXPECT_TRUE(r == Point(3.0 / 110.0, 0.0));
    EXPECT_TRUE(s == Point(110.0, -4.5));
}

TEST(pointTest, divisionAssignTest2) {
    Point p(3.0, 2.0);
    Real q = -5.7;
    p /= q;
    EXPECT_TRUE(p == Point(3.0 / -5.7, 2.0 / -5.7));
    EXPECT_TRUE(q == -5.7);
    Point r(3.0, 0.0);
    Real s = 110.0;
    r /= s;
    EXPECT_TRUE(r == Point(3.0 / 110.0, 0.0));
    EXPECT_TRUE(s == 110.0);
}

TEST(pointTest, rotateTest) {
    Point p(3.0, 2.0);
    p.rotate(PI / 2);
    EXPECT_DOUBLE_EQ(p.x(), -2.0);
    EXPECT_DOUBLE_EQ(p.y(), 3.0);
    p.rotate(-PI);
    EXPECT_DOUBLE_EQ(p.x(), 2.0);
    EXPECT_DOUBLE_EQ(p.y(), -3.0);
    p.rotate(-3);
    EXPECT_DOUBLE_EQ(p.x(), -2.4033450173804924);
    EXPECT_DOUBLE_EQ(p.y(), 2.687737473681602);
}

TEST(pointTest, distanceTest1) {
    Point p(3.0, 2.0), q(0.0, -2.0);
    EXPECT_DOUBLE_EQ(p.distance(q), 5.0);
    EXPECT_DOUBLE_EQ(q.distance(p), 5.0);
    p += q;
    EXPECT_DOUBLE_EQ(p.distance(q), 3.605551275463989);
    EXPECT_DOUBLE_EQ(q.distance(p), 3.605551275463989);
    p += q;
    EXPECT_DOUBLE_EQ(p.distance(q), 3.0);
    EXPECT_DOUBLE_EQ(q.distance(p), 3.0);
}

TEST(pointTest, distanceTest2) {
    Point p(15.0, -8.0), q(0.0, -2.0);
    EXPECT_DOUBLE_EQ(p.distance(), 17.0);
    EXPECT_DOUBLE_EQ(q.distance(), 2.0);
}

TEST(pointTest, xdistTest) {
    Point p(3.0, 2.0), q(4.0, 2.0);
    EXPECT_DOUBLE_EQ(p.xdist(q), 1.0);
    EXPECT_DOUBLE_EQ(q.xdist(p), 1.0);
    q.x(3.0);
    EXPECT_DOUBLE_EQ(p.xdist(q), 0.0);
    EXPECT_DOUBLE_EQ(q.xdist(p), 0.0);
}

TEST(pointTest, ydistTest) {
    Point p(3.0, 2.0), q(4.0, 2.0);
    EXPECT_DOUBLE_EQ(p.ydist(q), 0.0);
    EXPECT_DOUBLE_EQ(q.ydist(p), 0.0);
    q.y(8.0);
    EXPECT_DOUBLE_EQ(p.ydist(q), 6.0);
    EXPECT_DOUBLE_EQ(q.ydist(p), 6.0);
}

TEST(pointTest, polarTest1) {
    EXPECT_TRUE(Point::polar(0).x() == 1.0);
    EXPECT_TRUE(Point::polar(0).y() == 0.0);
    EXPECT_TRUE(Point::polar(PI/2) == Point(0.0, 1.0));
    EXPECT_TRUE(Point::polar(PI)   == Point(-1.0, 0.0));
    EXPECT_DOUBLE_EQ(Point::polar(-3*PI/4).x(), -0.70710678118654724);
    EXPECT_DOUBLE_EQ(Point::polar(-3*PI/4).y(), -0.70710678118654724);
    EXPECT_DOUBLE_EQ(Point::polar(5*PI/6).x(), -0.866025403784438646);
    EXPECT_DOUBLE_EQ(Point::polar(5*PI/6).y(), 0.5);
}

TEST(pointTest, polarTest2) {
    EXPECT_TRUE(Point::polar(0, 10.0).x() == 10.0);
    EXPECT_TRUE(Point::polar(0, 10.0).y() == 0.0);
    EXPECT_TRUE(Point::polar(-PI/2, 10.0) == Point(0.0, -10.0));
    EXPECT_DOUBLE_EQ(Point::polar(5*PI/6, 10).x(), -8.66025403784438646);
    EXPECT_DOUBLE_EQ(Point::polar(5*PI/6, 10).y(), 5);
}

TEST(pointTest, absTest) {
    EXPECT_DOUBLE_EQ(abs(Point(3.0, 4.0)), 5.0);
    EXPECT_DOUBLE_EQ(abs(Point(-0.5, 0.5)), 0.70710678118654724);
    EXPECT_DOUBLE_EQ(abs(Point(0, 0)), 0);
    EXPECT_DOUBLE_EQ(abs(Point(0, -1)), 1);
}

TEST(pointTest, argTest) {
    EXPECT_NEAR(arg(Point(-1.9, -1e-15)), -PI, 1e-13);
    EXPECT_NEAR(arg(Point(4, -4)), -PI/4, 1e-13);
    EXPECT_NEAR(arg(Point(-1, 1.7320508075688772935274)), PI * 2 / 3, 1e-13);
}

TEST(pointTest, minusTest) {
    Point p(3.0, 2.0), q(4.0, -2.0);
    EXPECT_TRUE(-p == Point(-3.0, -2.0));
    EXPECT_TRUE(-q == Point(-4.0, 2.0));
    EXPECT_TRUE(-(-p) == p);
}