#!/bin/bash

taskName=$1
echo << EOF
#include <gtest/gtest.h>

TEST(${taskName}Test, ExampleTest)
{
    EXPECT_TRUE(true);
}
EOF