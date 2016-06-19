#include "../Common/InnerNode.hpp"
#include "../Common/LeafNode.hpp"
#include "../Common/Node.hpp"
#include "../DataAccess/File.hpp"
#include <iostream>
#include <string>
#include <memory>
#include "gtest/gtest.h"


#define PATH "./test.bin"

TEST(fileTest, InnerNode){
    std::cout << "Starting \n";

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


    file->deleteNode(positionOne);
    file->deleteNode(positionTwo);
    file->deleteNode(positionThree);

    delete file;
    return;

}


TEST(fileTest, buildAndRecover){
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

    std::cout << "Creating nodes \n";
    std::unique_ptr<LeafNode> pNodeOne(new LeafNode());
    std::unique_ptr<LeafNode> pNodeTwo(new LeafNode());
    std::unique_ptr<LeafNode> pNodeThree(new LeafNode());


    std::cout << "Saving registerss in nodes \n";

    pNodeOne->insertRegister(registerOne);
    pNodeOne->insertRegister(registerTwo);
    pNodeTwo->insertRegister(registerThree);
    pNodeThree->insertRegister(registerFour);

    ASSERT_EQ(1, pNodeOne->getRegister(1).getId());
    ASSERT_EQ(2, pNodeOne->getRegister(2).getId());
    ASSERT_EQ(3, pNodeTwo->getRegister(3).getId());
    ASSERT_EQ(4, pNodeThree->getRegister(4).getId());

    std::cout << "Creating file \n";

    File* file = new File(PATH, 4096);

    std::cout << "Nodes are saved and recovered\n";


    uint32_t positionOne = file->saveNode(pNodeOne.get());
    uint32_t positionTwo = file->saveNode(pNodeTwo.get());
    uint32_t positionThree = file->saveNode(pNodeThree.get());

    std::unique_ptr<LeafNode> pNodeOneRecovered((LeafNode*)file->getNode(positionOne));
    std::unique_ptr<LeafNode> pNodeTwoRecovered((LeafNode*)file->getNode(positionTwo));
    std::unique_ptr<LeafNode> pNodeThreeRecovered((LeafNode*)file->getNode(positionThree));

    ASSERT_EQ(1, pNodeOneRecovered->getRegister(1).getId());
    ASSERT_EQ(2, pNodeOneRecovered->getRegister(2).getId());
    ASSERT_EQ(3, pNodeTwoRecovered->getRegister(3).getId());
    ASSERT_EQ(4, pNodeThreeRecovered->getRegister(4).getId());

    file->deleteNode(positionOne);
    file->deleteNode(positionTwo);
    file->deleteNode(positionThree);

    delete file;
    return;

}


int main(int argc, char *argv[])
{

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
