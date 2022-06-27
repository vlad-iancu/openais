
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(Logger, Pass)
{
	using testing::Le;
	EXPECT_THAT(3, Le(4));
		
}
