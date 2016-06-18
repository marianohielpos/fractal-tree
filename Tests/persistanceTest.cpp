#include "../Common/InnerNode.hpp"
#include "../Common/LeafNode.hpp"
#include "../Common/Node.hpp"
#include "../DataAccess/File.hpp"
#include <iostream>
#include <string>
#include <memory>
#include "gtest/gtest.h"


#define PATH "./test.bin"

TEST(fileTest, buildAndRecover){
    std::cout << "Starting \n";
    char* codeOne = (char*)"111";
    char* codeTwo = (char*)"222";
    char* codeThree = (char*)"333";
    char* codeFour = (char*)"444";

    char* codeFive = (char*)"111";
    char* codeSix = (char*)"222";
    char* codeSeven = (char*)"333";
    char* codeEight = (char*)"444";


    char* descriptionOne = (char*)"descriptionOne";
    char* descriptionTwo = (char*)"descriptionTwo";
    char* descriptionThree = (char*)"descriptionThree";
    char* descriptionFour = (char*)"descriptionFour";

    char* descriptionFive = (char*)"descriptionFive";
    char* descriptionSix = (char*)"descriptionSix";
    char* descriptionSeven = (char*)"descriptionSeven";
    char* descriptionEight = (char*)"descriptionEight";

    std::cout << "Creating registerss \n";
    std::unique_ptr<Register> pRegisterOne(new Register(1, codeOne, descriptionOne));
    std::unique_ptr<Register> pRegisterTwo(new Register(2, codeTwo, descriptionTwo));
    std::unique_ptr<Register> pRegisterThree(new Register(3, codeThree, descriptionThree));
    std::unique_ptr<Register> pRegisterFour(new Register(4, codeFour, descriptionFour));

    std::unique_ptr<Register> pRegisterFive(new Register(1, codeFive, descriptionFive));
    std::unique_ptr<Register> pRegisterSix(new Register(2, codeSix, descriptionSix));
    std::unique_ptr<Register> pRegisterSeven(new Register(3, codeSeven, descriptionSeven));
    std::unique_ptr<Register> pRegisterEight(new Register(4, codeEight, descriptionEight));


    std::cout << "Creating nodes \n";
    std::unique_ptr<InnerNode> pNodeOne(new InnerNode());
    std::unique_ptr<InnerNode> pNodeTwo(new InnerNode());
    std::unique_ptr<InnerNode> pNodeThree(new InnerNode());


    std::cout << "Saving registerss in nodes \n";

    pNodeOne->insertReference(1,1);
    pNodeOne->insertReference(2,2);
    pNodeTwo->insertReference(3,3);
    pNodeThree->insertReference(4,4);

    ASSERT_EQ(1, pNodeOne->getReference(1));
    ASSERT_EQ(2, pNodeOne->getReference(2));
    ASSERT_EQ(3, pNodeTwo->getReference(3));
    ASSERT_EQ(4, pNodeThree->getReference(4));


    std::cout << "Creating file \n";

    File* file = new File(PATH, 4096);

    std::cout << "Nodes are saved and recovered\n";


    uint32_t positionOne = file->saveNode(pNodeOne.get());
    uint32_t positionTwo = file->saveNode(pNodeTwo.get());
    uint32_t positionThree = file->saveNode(pNodeThree.get());

    std::unique_ptr<InnerNode> pNodeOneRecovered((InnerNode*)file->getNode(positionOne));
    std::unique_ptr<InnerNode> pNodeTwoRecovered((InnerNode*)file->getNode(positionTwo));
    std::unique_ptr<InnerNode> pNodeThreeRecovered((InnerNode*)file->getNode(positionThree));

    ASSERT_EQ(1, pNodeOneRecovered->getReference(1));
    ASSERT_EQ(2, pNodeOneRecovered->getReference(2));
    ASSERT_EQ(3, pNodeTwoRecovered->getReference(3));
    ASSERT_EQ(4, pNodeThreeRecovered->getReference(4));


    delete file;
    return;

}


int main(int argc, char *argv[])
{

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
