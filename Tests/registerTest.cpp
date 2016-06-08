#include "../Common/Register.hpp"
#include <iostream>
#include <string>
#include <memory>
#include "gtest/gtest.h"

TEST(_registerTest, buildAndRecover) {
    char* codeOne = (char*)"111";
    char* codeTwo = (char*)"222";
    char* codeThree = (char*)"333";
    char* codeFour = (char*)"444";

    char* descriptionOne = (char*)"descriptionOne";
    char* descriptionTwo = (char*)"descriptionTwo";
    char* descriptionThree = (char*)"descriptionThree";
    char* descriptionFour = (char*)"descriptionFour";


    std::unique_ptr<Register> pRegisterOne(new Register(1, codeOne, descriptionOne));
    std::unique_ptr<Register> pRegisterTwo(new Register(2, codeTwo, descriptionTwo));
    std::unique_ptr<Register> pRegisterThree(new Register(3, codeThree, descriptionThree));
    std::unique_ptr<Register> pRegisterFour(new Register(4, codeFour, descriptionFour));

    ASSERT_STREQ(codeOne, (*pRegisterOne->getCode()).c_str());
    ASSERT_STREQ(codeTwo, (*pRegisterTwo->getCode()).c_str());
    ASSERT_STREQ(codeThree, (*pRegisterThree->getCode()).c_str());
    ASSERT_STREQ(codeFour, (*pRegisterFour->getCode()).c_str());

    ASSERT_EQ(1, *pRegisterOne->getId());
    ASSERT_EQ(2, *pRegisterTwo->getId());
    ASSERT_EQ(3, *pRegisterThree->getId());
    ASSERT_EQ(4, *pRegisterFour->getId());

    ASSERT_STREQ(descriptionOne, (*pRegisterOne->getDescription()).c_str());
    ASSERT_STREQ(descriptionTwo, (*pRegisterTwo->getDescription()).c_str());
    ASSERT_STREQ(descriptionThree, (*pRegisterThree->getDescription()).c_str());
    ASSERT_STREQ(descriptionFour, (*pRegisterFour->getDescription()).c_str());

}

int main(int argc, char *argv[])
{

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
