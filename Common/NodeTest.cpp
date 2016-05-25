#include "Node.hpp"
#include <iostream>
#include <string>

int main ()
{
    std::string COD1 ("111");
    std::string COD2 ("222");
    std::string COD3 ("333");
    std::string COD4 ("444");

    std::string descriptionOne ("descriptionOne");
    std::string descriptionTwo ("descriptionTwo");
    std::string descriptionThree ("descriptionThree");
    std::string descriptionFour ("descriptionFour");

    Node* nodeOne = new Node(1, COD1, descriptionOne);
    Node* nodeTwo = new Node(2, COD2, descriptionTwo);
    Node* nodeThree = new Node(3, COD3, descriptionThree);
    Node* nodeFour = new Node(4, COD4, descriptionFour);

    std::cout << (*nodeOne).getCode() << "\n";
    std::cout << (*nodeTwo).getCode() << "\n";
    std::cout << (*nodeThree).getCode() << "\n";
    std::cout << (*nodeFour).getCode() << "\n";

    std::cout << (*nodeOne).getId() << "\n";
    std::cout << (*nodeTwo).getId() << "\n";
    std::cout << (*nodeThree).getId() << "\n";
    std::cout << (*nodeFour).getId() << "\n";

    std::cout << (*nodeOne).getDescription() << "\n";
    std::cout << (*nodeTwo).getDescription() << "\n";
    std::cout << (*nodeThree).getDescription() << "\n";
    std::cout << (*nodeFour).getDescription() << "\n";


}
