#include "../Common/Registry.hpp"
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
    std::unique_ptr<Registry> pRegistryOne(new Registry(1, COD1, descriptionOne));
    std::unique_ptr<Registry> pRegistryTwo(new Registry(2, COD2, descriptionTwo));
    std::unique_ptr<Registry> pRegistryThree(new Registry(3, COD3, descriptionThree));
    std::unique_ptr<Registry> pRegistryFour(new Registry(4, COD4, descriptionFour));

    std::cout << "Testing \n";
    std::cout << *pRegistryOne->getCode() << "\n";
    std::cout << *pRegistryTwo->getCode() << "\n";
    std::cout << *pRegistryThree->getCode() << "\n";
    std::cout << *pRegistryFour->getCode() << "\n";

    std::cout << *pRegistryOne->getId() << "\n";
    std::cout << *pRegistryTwo->getId() << "\n";
    std::cout << *pRegistryThree->getId() << "\n";
    std::cout << *pRegistryFour->getId() << "\n";

    std::cout << *pRegistryOne->getDescription() << "\n";
    std::cout << *pRegistryTwo->getDescription() << "\n";
    std::cout << *pRegistryThree->getDescription() << "\n";
    std::cout << *pRegistryFour->getDescription() << "\n";


}
