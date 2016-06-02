#include "../Common/Node.hpp"
#include <iostream>
#include <string>
#include <memory>


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

    std::cout << "Testing \n";
    std::cout << *pNodeOne->getCode() << "\n";
    std::cout << *pNodeTwo->getCode() << "\n";
    std::cout << *pNodeThree->getCode() << "\n";
    std::cout << *pNodeFour->getCode() << "\n";

    std::cout << *pNodeOne->getId() << "\n";
    std::cout << *pNodeTwo->getId() << "\n";
    std::cout << *pNodeThree->getId() << "\n";
    std::cout << *pNodeFour->getId() << "\n";

    std::cout << *pNodeOne->getDescription() << "\n";
    std::cout << *pNodeTwo->getDescription() << "\n";
    std::cout << *pNodeThree->getDescription() << "\n";
    std::cout << *pNodeFour->getDescription() << "\n";


}
