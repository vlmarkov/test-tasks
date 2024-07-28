#include <gtest/gtest.h>

#include <module_a/module_a.hpp>


TEST(TestModuleAMedium, WithFiveExpectTwentyFive) { 
    ASSERT_EQ(10, module_a(5));
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
