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

    std::cout << "Creating _registers \n";
    std::unique_ptr<Register> pRegisterOne(new Register(1, codeOne, descriptionOne));
    std::unique_ptr<Register> pRegisterTwo(new Register(2, codeTwo, descriptionTwo));
    std::unique_ptr<Register> pRegisterThree(new Register(3, codeThree, descriptionThree));
    std::unique_ptr<Register> pRegisterFour(new Register(4, codeFour, descriptionFour));

    std::unique_ptr<Register> pRegisterFive(new Register(1, codeFive, descriptionFive));
    std::unique_ptr<Register> pRegisterSix(new Register(2, codeSix, descriptionSix));
    std::unique_ptr<Register> pRegisterSeven(new Register(3, codeSeven, descriptionSeven));
    std::unique_ptr<Register> pRegisterEight(new Register(4, codeEight, descriptionEight));


    std::cout << "Creating nodes \n";
    std::unique_ptr<Node> pNodeOne(new Node());
    std::unique_ptr<Node> pNodeTwo(new Node());
    std::unique_ptr<Node> pNodeThree(new Node());


    std::cout << "Saving _registers in nodes \n";

    pNodeOne->setRegister(*(pRegisterOne.get()));

    std::cout << "Creating file \n";

    File* file = new File(PATH, 4096);


    std::cout << "Nodes are saved and recovered\n";


    uint32_t position = file->saveNode(pNodeOne.get());

    std::unique_ptr<Node> pNodeOneRecovered(file->getNode(position));

    std::cout << pNodeOneRecovered->getRegister(0).getCode() << std::endl;
    std::cout << pNodeOneRecovered->getRegister(0).getDescription() << std::endl;
    std::cout << pNodeOneRecovered->getRegister(0).getId() << std::endl;

    ASSERT_STREQ(codeOne, (pNodeOneRecovered->getRegister(0).getCode()));
    ASSERT_STREQ(descriptionOne, (pNodeOneRecovered->getRegister(0).getDescription()));
    ASSERT_EQ(1, pNodeOneRecovered->getRegister(0).getId());


    delete file;
    return;

    file->saveNode(pNodeTwo.get());
    file->saveNode(pNodeThree.get());

    Node* nodeOneRecovered = file->getNode(1);

    Node* nodeTwoRecovered = file->getNode(2);

    Node* nodeThreeRecovered = file->getNode(3);

    Node* nodeFourRecovered = file->getNode(4);


    std::cout << "Nodes are modifyed";

    Node* nodeOne = file->getNode(1);
    file->saveNode(nodeOne);

    nodeOneRecovered = file->getNode(1);


    std::cout << "Nodes are deleted";

    file->deleteNode(1);
    nodeOneRecovered = file->getNode(1);

    if( nodeOneRecovered != NULL ){
        std::cout << "Fail";
        return;
    }

    file->deleteNode(1);
    file->deleteNode(2);
    file->deleteNode(3);

    nodeTwoRecovered = file->getNode(2);
    nodeThreeRecovered = file->getNode(3);
    nodeFourRecovered = file->getNode(4);

    if( nodeTwoRecovered != NULL && nodeThreeRecovered!= NULL && nodeFourRecovered != NULL){
        std::cout << "ok";
    }
    else{
        std::cout << "Fail";
        return;
    }

    delete nodeOneRecovered;
    delete nodeTwoRecovered;
    delete nodeThreeRecovered;
    delete nodeFourRecovered;
}


int main(int argc, char *argv[])
{

    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}
