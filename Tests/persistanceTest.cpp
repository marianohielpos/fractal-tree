#include "../Common/Node.hpp"
#include "../DataAccess/File.hpp"
#include <iostream>
#include <string>
#include <memory>

#define PATH "./test.bin"

void verifyEqualness(Node* a,Node* b){

    if( a->getId() == b->getId() ){
           std::cout << "OK";
           return;
       }

    std::cout << "Fail";
    return;
}

int main ()
{
    std::cout << "Starting \n";
    char* COD1 = (char*)"111";
    char* COD2 = (char*)"222";
    char* COD3 = (char*)"333";
    char* COD4 = (char*)"444";

    char* descriptionOne = (char*)"descriptionOne";
    char* descriptionTwo = (char*)"descriptionTwo";
    char* descriptionThree = (char*)"descriptionThree";
    char* descriptionFour = (char*)"descriptionFour";

    std::cout << "Creating nodes \n";
    std::unique_ptr<Node> pNodeOne(new Node(1, COD1, descriptionOne));
    std::unique_ptr<Node> pNodeTwo(new Node(2, COD2, descriptionTwo));
    std::unique_ptr<Node> pNodeThree(new Node(3, COD3, descriptionThree));
    std::unique_ptr<Node> pNodeFour(new Node(4, COD4, descriptionFour));


    std::cout << "Creating file \n";

    File* file = new File(PATH, 4096);


    std::cout << "Nodes are saved and recovered";

    file->saveNode(pNodeOne.get());
    return 0;

    Node* nodeOneRecovered = file->getNode(1);
    verifyEqualness(pNodeOne.get(), nodeOneRecovered);

    file->saveNode(pNodeTwo.get());
    Node* nodeTwoRecovered = file->getNode(2);
    verifyEqualness(pNodeTwo.get(), nodeOneRecovered);

    file->saveNode(pNodeThree.get());
    Node* nodeThreeRecovered = file->getNode(3);
    verifyEqualness(pNodeThree.get(), nodeOneRecovered);

    file->saveNode(pNodeFour.get());
    Node* nodeFourRecovered = file->getNode(4);
    verifyEqualness(pNodeFour.get(), nodeOneRecovered);


    std::cout << "Nodes are modifyed";

    Node* nodeOne = file->getNode(1);
    nodeOne->setDescription("Asd");
    file->saveNode(nodeOne);

    nodeOneRecovered = file->getNode(1);
    verifyEqualness(nodeOne, nodeOneRecovered);


    std::cout << "Nodes are deleted";

    file->deleteNode(1);
    nodeOneRecovered = file->getNode(1);

    if( nodeOneRecovered != NULL ){
        std::cout << "Fail";
        return 1;
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
        return 1;
    }

    delete nodeOneRecovered;
    delete nodeTwoRecovered;
    delete nodeThreeRecovered;
    delete nodeFourRecovered;

    return 0;
}
