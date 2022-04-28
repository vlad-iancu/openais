#include <Task/CommandLine.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(CommandLine, ConfigAndInterface)
{
    using namespace openais::task;
    using testing::SizeIs;
    using testing::Contains;
    using testing::VariantWith;
    using testing::Key;

    //Arrange
    int argc = 5;
    const char * const argv[5] = {
        "/Bin/TestTask",
        "--config",
        "frequency_hz=5",
        "--interface",
        "InterfaceName=ActualInterface"
    };

    //Act
    bool help;
    auto options = ParseCommandLineOptions(argc, argv, help);

    //Assert
    ASSERT_TRUE(options.has_value());
    Config taskConfig = options.value().first;
    Config interfaceConfig = options.value().second;
    EXPECT_FALSE(help);
    EXPECT_THAT(taskConfig, SizeIs(1));
    EXPECT_THAT(interfaceConfig, SizeIs(1));
    EXPECT_THAT(taskConfig, Contains(Key("frequency_hz")));
    EXPECT_THAT(interfaceConfig, Contains(Key("InterfaceName")));
    EXPECT_THAT(taskConfig["frequency_hz"], VariantWith<double>(5.0));
    EXPECT_THAT(interfaceConfig["InterfaceName"], VariantWith<string>("ActualInterface"));
}

TEST(CommandLine, OnlyConfig)
{
    using namespace openais::task;
    using testing::SizeIs;
    using testing::Contains;
    using testing::VariantWith;
    using testing::Key;

    //Arrange
    int argc = 3;
    const char * const argv[3] = {
        "/Bin/TestTask",
        "--config",
        "frequency_hz=5"
    };

    //Act
    bool help;
    auto options = ParseCommandLineOptions(argc, argv, help);

    //Assert
    ASSERT_TRUE(options.has_value());
    Config taskConfig = options.value().first;
    Config interfaceConfig = options.value().second;
    EXPECT_FALSE(help);
    EXPECT_THAT(taskConfig, SizeIs(1));
    EXPECT_THAT(interfaceConfig, SizeIs(0));
    EXPECT_THAT(taskConfig, Contains(Key("frequency_hz")));
    EXPECT_THAT(taskConfig["frequency_hz"], VariantWith<double>(5.0));
}

TEST(CommandLine, OnlyInterface)
{
    using namespace openais::task;
    using testing::SizeIs;
    using testing::Contains;
    using testing::VariantWith;
    using testing::Key;

    //Arrange
    int argc = 3;
    const char * const argv[3] = {
        "/Bin/TestTask",
        "--interface",
        "InterfaceName=ActualInterface"
    };

    //Act
    bool help;
    auto options = ParseCommandLineOptions(argc, argv, help);

    //Assert
    ASSERT_TRUE(options.has_value());
    Config taskConfig = options.value().first;
    Config interfaceConfig = options.value().second;
    EXPECT_FALSE(help);
    EXPECT_THAT(taskConfig, SizeIs(0));
    EXPECT_THAT(interfaceConfig, SizeIs(1));
    EXPECT_THAT(interfaceConfig, Contains(Key("InterfaceName")));
    EXPECT_THAT(interfaceConfig["InterfaceName"], VariantWith<string>("ActualInterface"));
}

TEST(CommandLine, Help)
{
    using namespace openais::task;
    using testing::SizeIs;

    //Arrange
    int argc = 2;
    const char * const argv[2] = {
        "/Bin/TestTask",
        "--help"
    };

    //Act
    bool help;
    auto options = ParseCommandLineOptions(argc, argv, help);

    //Assert
    ASSERT_TRUE(options.has_value());
    Config taskConfig = options.value().first;
    Config interfaceConfig = options.value().second;
    EXPECT_TRUE(help);
    EXPECT_THAT(taskConfig, SizeIs(0));
    EXPECT_THAT(interfaceConfig, SizeIs(0));
}

TEST(CommandLine, InvalidConfig)
{
    using namespace openais::task;
    using testing::SizeIs;

    //Arrange
    int argc = 3;
    const char * const argv[3] = {
        "/Bin/TestTask",
        "--config",
        "frequency="
    };

    //Act
    bool help;
    auto options = ParseCommandLineOptions(argc, argv, help);

    //Assert
    ASSERT_FALSE(options.has_value());
}

TEST(CommandLine, InvalidInterface)
{
    using namespace openais::task;
    using testing::SizeIs;

    //Arrange
    int argc = 3;
    const char * const argv[3] = {
        "/Bin/TestTask",
        "--interface",
        "InterfaceDbName="
    };

    //Act
    bool help;
    auto options = ParseCommandLineOptions(argc, argv, help);

    //Assert
    ASSERT_FALSE(options.has_value());
}