#define SPACE_MAP_NUMBER
#define ID_REGISTER_MAP_NUMBER

#include "../Common/Node.hpp"
#include "./File.hpp"


Persistance::Constructor(std::string pathToFile){
    this.file = new File(pathToFile);
}

Node* Persistance::getNode(size_t id){

    return this.file.getNode(id);
}

bool Persistance::saveNode(node){

    return this.file.saveNode(id);
}

void Persistance::findFreeSpace(char *freeSpaceMetadata){
    char* rawRegister =  this.file.getRegister(SPACE_MAP_NUMBER);

    //Analize the register to find free space
}

void Persistance::findRegisterAddress(int nodeId){
    char* rawRegister = this.file.getRegister(ID_REGISTER_MAP_NUMBER);

    //Analize the register to find the number where the node is in

}
