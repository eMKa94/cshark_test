#include "CppUTest/TestHarness.h"
#include <stdio.h>

TEST_GROUP(TemplateTestGroup){};

TEST(TemplateTestGroup, exampleTestShouldPass)
{
    CHECK_TRUE(true);
}
