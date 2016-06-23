#include "../Logic/FractalTree.hpp"
#include "../Common/InnerNode.hpp"
#include "../Common/LeafNode.hpp"
#include "../Common/Node.hpp"
#include "../DataAccess/File.hpp"
#include <iostream>
#include <string>
#include <memory>
#include "gtest/gtest.h"


#define PATH "./test.bin"
TEST(treeTest, amountTest){
    std::cout << "Starting \n";
    FractalTree* fractalTree = new FractalTree(PATH);

    char* codeOne = (char*)"111";

    char* descriptionOne = (char*)"descriptionOne";


    std::cout << "Creating registerss \n";


    for(uint32_t i = 1; i < 1000; i++){
        std::cout << "Inserting node " << i << std::endl;
        Register registerOne =  Register(i, codeOne, descriptionOne);
        fractalTree->setRegister(&registerOne);
        Register* registerOneRecovered = fractalTree->getRegister(i);
        ASSERT_EQ(i, registerOneRecovered->getId());
    }


    delete fractalTree;
    return;

}


TEST(treeTest, treeTest){
    std::cout << "Starting \n";
    char* codeOne = (char*)"111";
    char* codeTwo = (char*)"222";
    char* codeThree = (char*)"333";
    char* codeFour = (char*)"444";

    char* descriptionOne = (char*)"descriptionOne";
    char* descriptionTwo = (char*)"descriptionTwo";
    char* descriptionThree = (char*)"descriptionThree";
    char* descriptionFour = (char*)"descriptionFour";

    std::cout << "Creating registerss \n";
    Register registerOne =  Register(1, codeOne, descriptionOne);
    Register registerTwo =  Register(2, codeTwo, descriptionTwo);
    Register registerThree =  Register(3, codeThree, descriptionThree);
    Register registerFour =  Register(4, codeFour, descriptionFour);

    std::cout << "Creating tree \n";

    FractalTree* fractalTree = new FractalTree(PATH);

	fractalTree->setRegister(&registerOne);
	fractalTree->setRegister(&registerTwo);
	fractalTree->setRegister(&registerThree);
	fractalTree->setRegister(&registerFour);

	Register* registerOneRecovered = fractalTree->getRegister(1);
	Register* registerTwoRecovered = fractalTree->getRegister(2);
	Register* registerThreeRecovered = fractalTree->getRegister(3);
	Register* registerFourRecovered = fractalTree->getRegister(4);

	ASSERT_EQ(1, registerOneRecovered->getId());
	ASSERT_EQ(2, registerTwoRecovered->getId());
	ASSERT_EQ(3, registerThreeRecovered->getId());
	ASSERT_EQ(4, registerFourRecovered->getId());


    delete fractalTree;
    return;

}

int main(int argc, char *argv[])
{

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
