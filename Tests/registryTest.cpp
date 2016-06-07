#include "../Common/Registry.hpp"
#include <iostream>
#include <string>
#include <memory>
#include "gtest/gtest.h"

TEST(registryTest, buildAndRecover) {
    char* codeOne = (char*)"111";
    char* codeTwo = (char*)"222";
    char* codeThree = (char*)"333";
    char* codeFour = (char*)"444";

    char* descriptionOne = (char*)"descriptionOne";
    char* descriptionTwo = (char*)"descriptionTwo";
    char* descriptionThree = (char*)"descriptionThree";
    char* descriptionFour = (char*)"descriptionFour";


    std::unique_ptr<Registry> pRegistryOne(new Registry(1, codeOne, descriptionOne));
    std::unique_ptr<Registry> pRegistryTwo(new Registry(2, codeTwo, descriptionTwo));
    std::unique_ptr<Registry> pRegistryThree(new Registry(3, codeThree, descriptionThree));
    std::unique_ptr<Registry> pRegistryFour(new Registry(4, codeFour, descriptionFour));

    ASSERT_STREQ(codeOne, (*pRegistryOne->getCode()).c_str());
    ASSERT_STREQ(codeTwo, (*pRegistryTwo->getCode()).c_str());
    ASSERT_STREQ(codeThree, (*pRegistryThree->getCode()).c_str());
    ASSERT_STREQ(codeFour, (*pRegistryFour->getCode()).c_str());

    ASSERT_EQ(1, *pRegistryOne->getId());
    ASSERT_EQ(2, *pRegistryTwo->getId());
    ASSERT_EQ(3, *pRegistryThree->getId());
    ASSERT_EQ(4, *pRegistryFour->getId());

    ASSERT_STREQ(descriptionOne, (*pRegistryOne->getDescription()).c_str());
    ASSERT_STREQ(descriptionTwo, (*pRegistryTwo->getDescription()).c_str());
    ASSERT_STREQ(descriptionThree, (*pRegistryThree->getDescription()).c_str());
    ASSERT_STREQ(descriptionFour, (*pRegistryFour->getDescription()).c_str());

}

int main(int argc, char *argv[])
{

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
