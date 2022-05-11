#include <vector>

#include <config.hpp>
#include <line.hpp>
#include <segment.hpp>
#include <cross_point.hpp>

#include <gtest/gtest.h>

using namespace std;

using namespace sapphre15::geometry;

TEST(crossPointTest, LineAndLineTest) {
    Line l1(3.0, 4.0, 5.0),
         l2(-3.0, 2.0, 6.0),
         l3(0.0, 5.0, -3.0),
         l4(1.0, 0.0, -8.0);
    Point p1 = cross_point(l1, l2)[0],
          p2 = cross_point(l1, l3)[0],
          p3 = cross_point(l1, l4)[0],
          p4 = cross_point(l2, l3)[0],
          p5 = cross_point(l2, l4)[0],
          p6 = cross_point(l4, l3)[0];
    EXPECT_NEAR(p1.x(), 7.0/9.0, 1e-13);
    EXPECT_NEAR(p1.y(), -11.0/6.0, 1e-13);
    EXPECT_NEAR(p2.x(), -37.0/15.0, 1e-13);
    EXPECT_NEAR(p2.y(), 3.0/5.0, 1e-13);
    EXPECT_NEAR(p3.x(), 8.0, 1e-13);
    EXPECT_NEAR(p3.y(), -7.25, 1e-13);
    EXPECT_NEAR(p4.x(), 12.0/5.0, 1e-13);
    EXPECT_NEAR(p4.y(), 3.0/5.0, 1e-13);
    EXPECT_NEAR(p5.x(), 8.0, 1e-13);
    EXPECT_NEAR(p5.y(), 9.0, 1e-13);
    EXPECT_NEAR(p6.x(), 8.0, 1e-13);
    EXPECT_NEAR(p6.y(), 3.0/5.0, 1e-13);
}

TEST(crossPointTest, SegmentAndLineTest) {
    Segment sg1(Point(3.0, -1.0), Point(6.0, 2.0)),
            sg2(Point(-1.0, 7.0), Point(2.0, -2.0));
    Line l1(Point(4.0, -3.0), Point(4.0, -9.0)),
         l2(Point(2.5, -1.5), Point(0, 3.5)),
         l3(Point(6.0, 2.0), Point(-1.0, 7.0));
    vector<Point> p1 = cross_point(sg1, l1),
                  p2 = cross_point(sg1, l2),
                  p3 = cross_point(sg1, l3),
                  p4 = cross_point(sg2, l1),
                  p5 = cross_point(sg2, l2),
                  p6 = cross_point(sg2, l3);
    EXPECT_NEAR(p1[0].x(), 4.0, 1e-13);
    EXPECT_NEAR(p1[0].y(), 0.0, 1e-13);
    EXPECT_TRUE(p2.empty());
    EXPECT_NEAR(p3[0].x(), 6.0, 1e-13);
    EXPECT_NEAR(p3[0].y(), 2.0, 1e-13);
    EXPECT_TRUE(p4.empty());
    EXPECT_NEAR(p5[0].x(), 0.5, 1e-13);
    EXPECT_NEAR(p5[0].y(), 2.5, 1e-13);
    EXPECT_NEAR(p6[0].x(), -1.0, 1e-13);
    EXPECT_NEAR(p6[0].y(), 7.0, 1e-13);
}

TEST(crossPointTest, LineAndSegmentTest) {
    Line l1(Point(-4.0, -2.0), Point(5.0, 2.0)),
         l2(Point(-1.0, 3.0), Point(2.0, -2.0));
    Segment sg1(Point(-5.0, 0.0), Point(5.0, 0.0)),
            sg2(Point(-7.0, 4.0), Point(2.0, 2.5));
    vector<Point> p1 = cross_point(l1, sg1),
                  p2 = cross_point(l1, sg2),
                  p3 = cross_point(l2, sg1),
                  p4 = cross_point(l2, sg2);
    EXPECT_NEAR(p1[0].x(), 0.5, 1e-13);
    EXPECT_NEAR(p1[0].y(), 0.0, 1e-13);
    EXPECT_TRUE(p2.empty());
    EXPECT_NEAR(p3[0].x(), 0.8, 1e-13);
    EXPECT_NEAR(p3[0].y(), 0.0, 1e-13);
    EXPECT_NEAR(p4[0].x(), -1.0, 1e-13);
    EXPECT_NEAR(p4[0].y(), 3.0, 1e-13);
}

TEST(crossPointTest, SegmentAndSegmentTest) {
    Segment sg1(Point(-1.0, 0.0), Point(0.0, 2.0)),
            sg2(Point(-3.0, 4.0), Point(2.0, -1.0)),
            sg3(Point(0.5, -0.5), Point(-4.0, 1.0));
    vector<Point> p1 = cross_point(sg1, sg2),
                  p2 = cross_point(sg2, sg3),
                  p3 = cross_point(sg3, sg1);
    EXPECT_NEAR(p1[0].x(), -1.0/3.0, 1e-13);
    EXPECT_NEAR(p1[0].y(), 4.0/3.0, 1e-13);
    EXPECT_TRUE(p2.empty());
    EXPECT_NEAR(p3[0].x(), -1.0, 1e-13);
    EXPECT_NEAR(p3[0].y(), 0.0, 1e-13);
}

TEST(crossPointTest, CircleAndLineTest) {
    Circle c1(Point(3.0, -1.0), 5.0),
           c2(Point(0.0, -2.0), 1.0),
           c3(Point(-12.0, 1.0), 10.0);
    Line l1(3.0, -4.0, 12.0),
         l2(1.0, 0.0, 1.0);
    auto v11 = cross_point(c1, l1),
         v12 = cross_point(c1, l2),
         v21 = cross_point(c2, l1),
         v22 = cross_point(c2, l2),
         v31 = cross_point(c3, l1),
         v32 = cross_point(c3, l2);
    EXPECT_EQ(v11.size(), 1);
    EXPECT_DOUBLE_EQ(v11[0].x(), 0.0);
    EXPECT_DOUBLE_EQ(v11[0].y(), 3.0);
    EXPECT_EQ(v12.size(), 2);
    EXPECT_DOUBLE_EQ(v12[0].x(), -1.0);
    EXPECT_DOUBLE_EQ(v12[0].y(), 2.0);
    EXPECT_DOUBLE_EQ(v12[1].x(), -1.0);
    EXPECT_DOUBLE_EQ(v12[1].y(), -4.0);
    EXPECT_TRUE(v21.empty());
    EXPECT_EQ(v22.size(), 1);
    EXPECT_DOUBLE_EQ(v22[0].x(), -1.0);
    EXPECT_DOUBLE_EQ(v22[0].y(), -2.0);
    EXPECT_EQ(v31.size(), 2);
    EXPECT_DOUBLE_EQ(v31[0].x(), -2.012059143293446705769156324095);
    EXPECT_DOUBLE_EQ(v31[0].y(), 1.490955642529915081695435219444);
    EXPECT_DOUBLE_EQ(v31[1].x(), -15.267940856706553987010011042003);
    EXPECT_DOUBLE_EQ(v31[1].y(), -8.450955642529914157989878731314);
    EXPECT_TRUE(v32.empty());
}

TEST(crossPointTest, LineAndCircleTest) {
    Circle c1(Point(4.0, -1.0), 297.0);
    Line l1(128.0, 268.0, -88452.0);
    auto v11 = cross_point(c1, l1);
    EXPECT_EQ(v11.size(), 2);
    EXPECT_DOUBLE_EQ(v11[0].x(), 131.097637982719589899716083891690);
    EXPECT_DOUBLE_EQ(v11[0].y(), 267.430978873924971139786066487432);
    EXPECT_DOUBLE_EQ(v11[1].x(), 132.902362017280410100283916108310);
    EXPECT_DOUBLE_EQ(v11[1].y(), 266.569021126075028860213933512568);
}

TEST(crossPointTest, CircleAndCircleTest1) {
    Circle c1(Point(0.0,  1.0), 12.0),
           c2(Point(0.0,  1.0), 10.0),
           c3(Point(0.0,  1.0),  6.0),
           c4(Point(9.0,  1.0),  3.0),
           c5(Point(0.0, -8.0),  3.0);
    auto v12 = cross_point(c1, c2),
         v13 = cross_point(c1, c3),
         v14 = cross_point(c1, c4),
         v15 = cross_point(c1, c5),
         v21 = cross_point(c2, c1),
         v23 = cross_point(c2, c3),
         v24 = cross_point(c2, c4),
         v25 = cross_point(c2, c5),
         v31 = cross_point(c3, c1),
         v32 = cross_point(c3, c2),
         v34 = cross_point(c3, c4),
         v35 = cross_point(c3, c5),
         v41 = cross_point(c4, c1),
         v42 = cross_point(c4, c2),
         v43 = cross_point(c4, c3),
         v45 = cross_point(c4, c5),
         v51 = cross_point(c5, c1),
         v52 = cross_point(c5, c2),
         v53 = cross_point(c5, c3),
         v54 = cross_point(c5, c4);
    EXPECT_EQ(v12.size(), 0);
    EXPECT_EQ(v21.size(), 0);
    EXPECT_EQ(v13.size(), 0);
    EXPECT_EQ(v31.size(), 0);
    EXPECT_EQ(v14.size(), 1);
    EXPECT_DOUBLE_EQ(v14[0].x(), 12.0);
    EXPECT_DOUBLE_EQ(v14[0].y(),  1.0);
    EXPECT_EQ(v41.size(), 1);
    EXPECT_DOUBLE_EQ(v41[0].x(), 12.0);
    EXPECT_DOUBLE_EQ(v41[0].y(),  1.0);
    EXPECT_EQ(v15.size(), 1);
    EXPECT_DOUBLE_EQ(v15[0].x(), 0.0);
    EXPECT_DOUBLE_EQ(v15[0].y(), -11.0);
    EXPECT_EQ(v51.size(), 1);
    EXPECT_DOUBLE_EQ(v51[0].x(), 0.0);
    EXPECT_DOUBLE_EQ(v51[0].y(), -11.0);
    EXPECT_EQ(v23.size(), 0);
    EXPECT_EQ(v32.size(), 0);
    EXPECT_EQ(v24.size(), 2);
    EXPECT_DOUBLE_EQ(v24[0].x(), 86.0/9.0);
    // EXPECT_DOUBLE_EQ(v24[0].y(), 3.9481109247603556333672259);
    EXPECT_DOUBLE_EQ(v24[1].x(), 86.0/9.0);
    // EXPECT_DOUBLE_EQ(v24[1].y(), -1.9481109247603554113226210);
    EXPECT_EQ(v42.size(), 2);
    EXPECT_DOUBLE_EQ(v42[0].x(), 86.0/9.0);
    EXPECT_DOUBLE_EQ(v42[0].y(), 3.9481109247603556333672259);
    EXPECT_DOUBLE_EQ(v42[1].x(), 86.0/9.0);
    EXPECT_DOUBLE_EQ(v42[1].y(), -1.9481109247603554113226210);
    EXPECT_EQ(v25.size(), 2);
    // EXPECT_DOUBLE_EQ(v25[0].x(), 2.9481109247603556333672259);
    EXPECT_DOUBLE_EQ(v25[0].y(), -77.0/9.0);
    // EXPECT_DOUBLE_EQ(v25[1].x(), -2.9481109247603556333672259);
    EXPECT_DOUBLE_EQ(v25[1].y(), -77.0/9.0);
    EXPECT_EQ(v52.size(), 2);
    EXPECT_DOUBLE_EQ(v52[0].x(), 2.9481109247603556333672259);
    EXPECT_DOUBLE_EQ(v52[0].y(), -77.0/9.0);
    EXPECT_DOUBLE_EQ(v52[1].x(), -2.9481109247603556333672259);
    EXPECT_DOUBLE_EQ(v52[1].y(), -77.0/9.0);
    EXPECT_EQ(v34.size(), 1);
    EXPECT_DOUBLE_EQ(v34[0].x(), 6.0);
    EXPECT_DOUBLE_EQ(v34[0].y(), 1.0);
    EXPECT_EQ(v43.size(), 1);
    EXPECT_DOUBLE_EQ(v43[0].x(), 6.0);
    EXPECT_DOUBLE_EQ(v43[0].y(), 1.0);
    EXPECT_EQ(v35.size(), 1);
    EXPECT_DOUBLE_EQ(v35[0].x(),  0.0);
    EXPECT_DOUBLE_EQ(v35[0].y(), -5.0);
    EXPECT_EQ(v53.size(), 1);
    EXPECT_DOUBLE_EQ(v53[0].x(),  0.0);
    EXPECT_DOUBLE_EQ(v53[0].y(), -5.0);
    EXPECT_EQ(v54.size(), 0);
    EXPECT_EQ(v45.size(), 0);
}

TEST(crossPointTest, CircleAndCircleTest2) {
    Circle c1(Point(-9.0, 6.0), 2.0),
           c2(Point(-5.0, 9.0), 3.0),
           c3(Point(-6.0, 2.0), 7.0),
           c4(Point(5.0, -1.0), 13.0);
    auto v12 = cross_point(c1, c2),
         v13 = cross_point(c1, c3),
         v14 = cross_point(c1, c4),
         v21 = cross_point(c2, c1),
         v23 = cross_point(c2, c3),
         v24 = cross_point(c2, c4),
         v31 = cross_point(c3, c1),
         v32 = cross_point(c3, c2),
         v34 = cross_point(c3, c4),
         v41 = cross_point(c4, c1),
         v42 = cross_point(c4, c2),
         v43 = cross_point(c4, c3);
    EXPECT_EQ(v12.size(), 1);
    EXPECT_DOUBLE_EQ(v12[0].x(), -7.4);
    EXPECT_DOUBLE_EQ(v12[0].y(), 7.2);
    EXPECT_EQ(v21.size(), 1);
    EXPECT_DOUBLE_EQ(v21[0].x(), -7.4);
    EXPECT_DOUBLE_EQ(v21[0].y(), 7.2);
    EXPECT_EQ(v13.size(), 1);
    EXPECT_DOUBLE_EQ(v13[0].x(), -10.2);
    EXPECT_DOUBLE_EQ(v13[0].y(), 7.6);
    EXPECT_EQ(v31.size(), 1);
    EXPECT_DOUBLE_EQ(v31[0].x(), -10.2);
    EXPECT_DOUBLE_EQ(v31[0].y(), 7.6);
    EXPECT_EQ(v14.size(), 0);
    EXPECT_EQ(v41.size(), 0);
    EXPECT_EQ(v23.size(), 2);
    EXPECT_DOUBLE_EQ(v23[0].x(), -7.9861739379323619658634925);
    EXPECT_DOUBLE_EQ(v23[0].y(), 8.7123105625617665026538816);
    EXPECT_DOUBLE_EQ(v23[1].x(), -2.2138260620676377676829816);
    EXPECT_DOUBLE_EQ(v23[1].y(), 7.8876894374382340302531702);
    EXPECT_EQ(v32.size(), 2);
    EXPECT_DOUBLE_EQ(v32[0].x(), -7.9861739379323619658634925);
    EXPECT_DOUBLE_EQ(v32[0].y(), 8.7123105625617665026538816);
    EXPECT_DOUBLE_EQ(v32[1].x(), -2.2138260620676377676829816);
    EXPECT_DOUBLE_EQ(v32[1].y(), 7.8876894374382340302531702);
    EXPECT_EQ(v24.size(), 2);
    EXPECT_DOUBLE_EQ(v24[0].x(), -5.8708286933869704427024772);
    EXPECT_DOUBLE_EQ(v24[0].y(), 6.1291713066130295572975228);
    EXPECT_DOUBLE_EQ(v24[1].x(), -2.1291713066130291132083130);
    EXPECT_DOUBLE_EQ(v24[1].y(), 9.8708286933869704427024772);
    EXPECT_EQ(v42.size(), 2);
    EXPECT_DOUBLE_EQ(v42[0].x(), -5.8708286933869704427024772);
    EXPECT_DOUBLE_EQ(v42[0].y(), 6.1291713066130295572975228);
    EXPECT_DOUBLE_EQ(v42[1].x(), -2.1291713066130291132083130);
    EXPECT_DOUBLE_EQ(v42[1].y(), 9.8708286933869704427024772);
    EXPECT_EQ(v43.size(), 2);
    EXPECT_DOUBLE_EQ(v43[0].x(), -7.4151271142487047427493962);
    EXPECT_DOUBLE_EQ(v43[0].y(), -4.8554660855785822803909468);
    EXPECT_DOUBLE_EQ(v43[1].x(), -3.7387190395974494450115344);
    EXPECT_DOUBLE_EQ(v43[1].y(), 8.6246968548093523310171804);
    EXPECT_EQ(v34.size(), 2);
    EXPECT_DOUBLE_EQ(v34[0].x(), -7.4151271142487047427493962);
    EXPECT_DOUBLE_EQ(v34[0].y(), -4.8554660855785822803909468);
    EXPECT_DOUBLE_EQ(v34[1].x(), -3.7387190395974494450115344);
    EXPECT_DOUBLE_EQ(v34[1].y(), 8.6246968548093523310171804);
}