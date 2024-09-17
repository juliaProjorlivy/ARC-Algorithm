#include <gmock/gmock.h>
#include <gtest/gtest.h>

int main(int argc, char *argv[])
{
    printf("strart unit testing...from julan\n");
    ::testing::InitGoogleMock(&argc, argv);
    return RUN_ALL_TESTS();
}

