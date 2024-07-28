#include <gtest/gtest.h>

#include <module_b/module_b.hpp>


TEST(TestModuleBMedium, WithFiveExpectTwentyFive) { 
    ASSERT_EQ(25, module_b(5));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
