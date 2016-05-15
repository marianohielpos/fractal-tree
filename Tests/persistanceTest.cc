#include "../common/Node.h"
#include "../DataAccess/Persistance.h"
#include <iostream>


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
    Node::Node nodeOne = new Node();
    Node::Node nodeTwo = new Node();
    Node::Node nodeThree = new Node();
    Node::Node nodeFour = new Node();

    Persistance::Persistance persistance = new Persistance(PATH);


    std::cout << "Nodes are saved and recovered";

    persistance.saveNode(node1);
    Node::node nodeOneRecovered = persistance.getNode(1);
    verifyEqualness(nodeOne, nodeOneRecovered);

    persistance.saveNode(nodeTwo);
    Node::node nodeTwoRecovered = persistance.getNode(2);
    verifyEqualness(nodeTwo, nodeOneRecovered);

    persistance.saveNode(nodeThree);
    Node::node nodeThreeRecovered = persistance.getNode(3);
    verifyEqualness(nodeThree, nodeOneRecovered);

    persistance.saveNode(nodeFour);
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
