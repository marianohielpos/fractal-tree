#include "../common/Node.h"
#include "../DataAccess/Persistance.h"
#include <iostream>
#include <string>
#include <memory>

#define PATH "./test.bin"

void verifyEqualness(Node::node a,Node::node b){

    if( a.getCode() == b.getCode()
       && a.getDescription() == b.getDescription()
       && a.getId() == b-getId() ){
           return std::cout << "OK";
       }

    return std::cout << "Fail";
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

    Persistance::Persistance persistance = new Persistance(PATH);


    std::cout << "Nodes are saved and recovered";

    persistance.saveNode(pNodeOne);
    Node::node nodeOneRecovered = persistance.getNode(1);
    verifyEqualness(nodeOne, nodeOneRecovered);

    persistance.saveNode(pNodeTwo);
    Node::node nodeTwoRecovered = persistance.getNode(2);
    verifyEqualness(nodeTwo, nodeOneRecovered);

    persistance.saveNode(pNodeThree);
    Node::node nodeThreeRecovered = persistance.getNode(3);
    verifyEqualness(nodeThree, nodeOneRecovered);

    persistance.saveNode(pNodeFour);
    Node::node nodeFourRecovered = persistance.getNode(4);
    verifyEqualness(nodeFour, nodeOneRecovered);


    std::cout << "Nodes are modifyed";

    Node::node nodeOne = persistance.getNode(1);
    nodeOne.setDescription("Asd");
    persistance.saveNode(nodeOne);

    Node::node nodeOneRecovered = persistance.getNode(1);
    verifyEqualness(nodeOne, nodeOneRecovered);


    std::cout << "Nodes are deleted";

    persistance.deleteNode(1);
    Node::node nodeOneRecovered = persistance.getNode(1);

    if( nodeOneRecovered != null ){
        return std::cout << "Fail";
    }

    persistance.deleteNode(1);
    persistance.deleteNode(2);
    persistance.deleteNode(3);

    Node::node nodeTwoRecovered = persistance.getNode(2);
    Node::node nodeThreeRecovered = persistance.getNode(3);
    Node::node nodeFourRecovered = persistance.getNode(4);

    if( nodeTwoRecovered != null && nodeThreeRecovered!= null && nodeFourRecovered != null){
        return std::cout << "ok";
    }
    else{
        return std::cout << "Fail";
    }

    delete nodeOneRecovered;
    delete nodeTwoRecovered;
    delete nodeThreeRecovered;
    delete nodeFourRecovered;

    return 0;
}
