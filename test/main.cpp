#include <gtest/gtest.h>

int main() {
    ::testing::InitGoogleTest();
    std::cout << "TEST" << std::endl;
    return RUN_ALL_TESTS();
}
