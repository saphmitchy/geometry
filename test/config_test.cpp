#include <config.hpp>

#include <gtest/gtest.h>

using namespace sapphre15::geometry;

TEST(sgn_test, sgn_test) {
    EXPECT_EQ(sgn(5.5), 1);
    EXPECT_EQ(sgn(0.00003), 1);
    EXPECT_EQ(sgn(0.00000000001), 0);
    EXPECT_EQ(sgn(0), 0);
    EXPECT_EQ(sgn(-3), -1);
    EXPECT_EQ(sgn(-0.00001), -1);
}

TEST(eq_test, eq_case) {
    EXPECT_TRUE(eq(100, 100));
    EXPECT_TRUE(eq(0, 0));
    EXPECT_TRUE(eq(-1, -1));
    EXPECT_TRUE(eq(-1, -1.000000000002));
    EXPECT_TRUE(eq(1, 1.00000000009));
    EXPECT_TRUE(eq(100000000010.0, 100000000008.0));
}

TEST(eq_test, neq_case) {
    EXPECT_FALSE(eq(100, 99));
    EXPECT_FALSE(eq(0, 0.1));
    EXPECT_FALSE(eq(-1.0, 1.0));
    EXPECT_FALSE(eq(-1.0, 0.1));
    EXPECT_FALSE(eq(-1, -1.000000002));
    EXPECT_FALSE(eq(0.0000001, 0.0));
    EXPECT_FALSE(eq(10000000.0, 10000001.0));
    EXPECT_FALSE(eq(-100000, -100001));
}