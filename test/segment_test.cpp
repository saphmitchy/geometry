#include <gtest/gtest.h>

#include <config.hpp>
#include <segment.hpp>

using namespace std;

using namespace sapphre15::geometry;

TEST(segmentTest, onObjectTest) {
    Segment sg;
    EXPECT_TRUE(sg.on_object(Point(0.5, 0.5)));
    EXPECT_FALSE(sg.on_object(Point(3.0, -2.1)));
    EXPECT_FALSE(sg.on_object(Point(3.0, -2.0)));
    EXPECT_FALSE(sg.on_object(Point(-3.0, -4.0)));
}

TEST(segmentTest, endPointsConstructorTest) {
    Segment sg1(Point(3.0, -4.0), Point(-1.0, 8.0));
    EXPECT_TRUE(sg1.on_object(Point(0.5, 3.5)));
    EXPECT_FALSE(sg1.on_object(Point(-2.0, 11.0)));
    EXPECT_FALSE(sg1.on_object(Point(3.1, -4.3)));
    EXPECT_FALSE(sg1.on_object(Point(-3.0, -4.0)));
}

TEST(segmentTest, directionConstructorTest) {
    Segment sg1(Point(-3.0, 2.0), PI / 4, 4.0);
    EXPECT_TRUE(sg1.on_object(Point(-1.0, 4.0)));
    EXPECT_TRUE(sg1.on_object(Point(sqrt(2.0) * 2 - 3.0, sqrt(2.0) * 2 + 2.0)));
    EXPECT_FALSE(sg1.on_object(Point(-5.0, 0.0)));
    EXPECT_FALSE(sg1.on_object(Point(9.0, 14.0)));
    Segment sg2(Point(-3.0, 2.0), PI, 0.5);
    EXPECT_TRUE(sg2.on_object(Point(-3.5, 2.0)));
    EXPECT_TRUE(sg2.on_object(Point(-3.0, 2.0)));
    EXPECT_FALSE(sg2.on_object(Point(0.0, 2.0)));
    EXPECT_FALSE(sg2.on_object(Point(3.4, 2.1)));
}

TEST(segmentTest, startTest) {
    Segment sg1(Point(3.0, 4.0), Point(0.0, -3.0)),
        sg2(Point(1.0, 3.0), Point(7.0, 10.0));
    EXPECT_TRUE(sg1.start() == Point(3.0, 4.0));
    EXPECT_TRUE(sg2.start() == Point(1.0, 3.0));
}

TEST(segmentTest, endTest) {
    Segment sg1(Point(3.0, 4.0), Point(0.0, -3.0)),
        sg2(Point(1.0, 3.0), Point(7.0, 10.0));
    EXPECT_TRUE(sg1.end() == Point(0.0, -3.0));
    EXPECT_TRUE(sg2.end() == Point(7.0, 10.0));
}

TEST(segmentTest, x1Test) {
    Segment sg1(Point(3.0, 4.0), Point(0.0, -3.0)),
        sg2(Point(1.0, 3.0), Point(7.0, 10.0));
    EXPECT_DOUBLE_EQ(sg1.x1(), 3.0);
    EXPECT_DOUBLE_EQ(sg2.x1(), 1.0);
}

TEST(segmentTest, y1Test) {
    Segment sg1(Point(3.0, 4.0), Point(0.0, -3.0)),
        sg2(Point(1.0, 3.0), Point(7.0, 10.0));
    EXPECT_DOUBLE_EQ(sg1.y1(), 4.0);
    EXPECT_DOUBLE_EQ(sg2.y1(), 3.0);
}

TEST(segmentTest, x2Test) {
    Segment sg1(Point(3.0, 4.0), Point(0.0, -3.0)),
        sg2(Point(1.0, 3.0), Point(7.0, 10.0));
    EXPECT_DOUBLE_EQ(sg1.x2(), 0.0);
    EXPECT_DOUBLE_EQ(sg2.x2(), 7.0);
}

TEST(segmentTest, y2Test) {
    Segment sg1(Point(3.0, 4.0), Point(0.0, -3.0)),
        sg2(Point(1.0, 3.0), Point(7.0, 10.0));
    EXPECT_DOUBLE_EQ(sg1.y2(), -3.0);
    EXPECT_DOUBLE_EQ(sg2.y2(), 10.0);
}

TEST(segmentTest, dxTest) {
    Segment sg1(Point(3.0, 4.0), Point(0.0, -3.0)),
        sg2(Point(1.0, 3.0), Point(7.0, 10.0));
    EXPECT_DOUBLE_EQ(sg1.dx(), 3.0);
    EXPECT_DOUBLE_EQ(sg2.dx(), 6.0);
}

TEST(segmentTest, dyTest) {
    Segment sg1(Point(3.0, 4.0), Point(0.0, -3.0)),
        sg2(Point(1.0, 3.0), Point(7.0, 10.0));
    EXPECT_DOUBLE_EQ(sg1.dy(), 7.0);
    EXPECT_DOUBLE_EQ(sg2.dy(), 7.0);
}

TEST(segmentTest, lengthTest) {
    Segment sg1(Point(3.0, 4.0), Point(0.0, 8.0)),
        sg2(Point(1.0, -3.0), Point(7.0, -3.0)),
        sg3(Point(1.0, 5.0), Point(1.0, -3.0));
    EXPECT_DOUBLE_EQ(sg1.length(), 5.0);
    EXPECT_DOUBLE_EQ(sg2.length(), 6.0);
    EXPECT_DOUBLE_EQ(sg3.length(), 8.0);
}

TEST(segmentTest, endPointsTest) {
    Segment sg(Point(3.0, 4.0), Point(-1.0, 0.0));
    EXPECT_TRUE(sg.end_points() ==
                make_pair(Point(3.0, 4.0), Point(-1.0, 0.0)));
}

TEST(segmentTest, translationTest) {
    Segment sg(Point(3.0, 4.0), Point(-1.0, 0.0));
    Segment sg1 = sg.translation(Point(-2.0, 5.0)),
            sg2 = sg.translation(Point(0.0, 0.0));
    EXPECT_DOUBLE_EQ(sg1.x1(), 1.0);
    EXPECT_DOUBLE_EQ(sg1.x2(), -3.0);
    EXPECT_DOUBLE_EQ(sg1.y1(), 9.0);
    EXPECT_DOUBLE_EQ(sg1.y2(), 5.0);
    EXPECT_DOUBLE_EQ(sg2.x1(), 3.0);
    EXPECT_DOUBLE_EQ(sg2.x2(), -1.0);
    EXPECT_DOUBLE_EQ(sg2.y1(), 4.0);
    EXPECT_DOUBLE_EQ(sg2.y2(), 0.0);
}

TEST(segmentTest, moveXTest) {
    Segment sg(Point(3.0, 4.0), Point(-1.0, 0.0));
    Segment sg1 = sg.moveX(4.0), sg2 = sg.moveX(0.0);
    EXPECT_DOUBLE_EQ(sg1.x1(), 7.0);
    EXPECT_DOUBLE_EQ(sg1.x2(), 3.0);
    EXPECT_DOUBLE_EQ(sg1.y1(), 4.0);
    EXPECT_DOUBLE_EQ(sg1.y2(), 0.0);
    EXPECT_DOUBLE_EQ(sg2.x1(), 3.0);
    EXPECT_DOUBLE_EQ(sg2.x2(), -1.0);
    EXPECT_DOUBLE_EQ(sg2.y1(), 4.0);
    EXPECT_DOUBLE_EQ(sg2.y2(), 0.0);
}

TEST(segmentTest, moveYTest) {
    Segment sg(Point(3.0, 4.0), Point(-1.0, 0.0));
    Segment sg1 = sg.moveY(-4.0), sg2 = sg.moveY(0.0);
    EXPECT_DOUBLE_EQ(sg1.x1(), 3.0);
    EXPECT_DOUBLE_EQ(sg1.x2(), -1.0);
    EXPECT_DOUBLE_EQ(sg1.y1(), 0.0);
    EXPECT_DOUBLE_EQ(sg1.y2(), -4.0);
    EXPECT_DOUBLE_EQ(sg2.x1(), 3.0);
    EXPECT_DOUBLE_EQ(sg2.x2(), -1.0);
    EXPECT_DOUBLE_EQ(sg2.y1(), 4.0);
    EXPECT_DOUBLE_EQ(sg2.y2(), 0.0);
}

TEST(segmentTest, moveVTest) {
    Segment sg(Point(2.0, 4.0), Point(-1.0, 0.0));
    Segment sg1 = sg.moveV(1.0), sg2 = sg.moveV(-2.0), sg3 = sg.moveV(0.0);
    EXPECT_DOUBLE_EQ(sg1.x1(), 2.8);
    EXPECT_DOUBLE_EQ(sg1.x2(), -0.2);
    EXPECT_DOUBLE_EQ(sg1.y1(), 3.4);
    EXPECT_DOUBLE_EQ(sg1.y2(), -0.6);
    EXPECT_DOUBLE_EQ(sg2.x1(), 0.4);
    EXPECT_DOUBLE_EQ(sg2.x2(), -2.6);
    EXPECT_DOUBLE_EQ(sg2.y1(), 5.2);
    EXPECT_DOUBLE_EQ(sg2.y2(), 1.2);
    EXPECT_DOUBLE_EQ(sg3.x1(), 2.0);
    EXPECT_DOUBLE_EQ(sg3.x2(), -1.0);
    EXPECT_DOUBLE_EQ(sg3.y1(), 4.0);
    EXPECT_DOUBLE_EQ(sg3.y2(), 0.0);
}

TEST(segmentTest, rotateTest) {
    Segment sg(Point(3.0, 4.0), Point(-1.0, 0.0));
    Segment sg1 = sg.rotate(PI / 2), sg2 = sg.rotate(-PI * 3 / 4),
            sg3 = sg.rotate(0.0);
    EXPECT_DOUBLE_EQ(sg1.x1(), 3.0);
    EXPECT_DOUBLE_EQ(sg1.x2(), 7.0);
    EXPECT_DOUBLE_EQ(sg1.y1(), 4.0);
    EXPECT_DOUBLE_EQ(sg1.y2(), 0.0);
    EXPECT_DOUBLE_EQ(sg2.x1(), 3.0);
    EXPECT_DOUBLE_EQ(sg2.x2(), 3.0);
    EXPECT_DOUBLE_EQ(sg2.y1(), 4.0);
    EXPECT_DOUBLE_EQ(sg2.y2(), 4.0 + sqrt(32));
    EXPECT_DOUBLE_EQ(sg3.x1(), 3.0);
    EXPECT_DOUBLE_EQ(sg3.x2(), -1.0);
    EXPECT_DOUBLE_EQ(sg3.y1(), 4.0);
    EXPECT_DOUBLE_EQ(sg3.y2(), 0.0);
}