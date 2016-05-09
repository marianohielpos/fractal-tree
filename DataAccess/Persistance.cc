
#define SPACE_MAP_NUMBER
#define ID_REGISTER_MAP_NUMBER


Persistance::Constructor(std::string pathToFile){
    this.file = new File(pathToFile);

}

Persistance::getNode(int id){

    throw 1; //Couldn't finde node

    return node;
}

Persistance::saveNode(node){

    throw 1; //Node doesn't fit

    return 0;
}

Persistance::findFreeSpace(char *freeSpaceMetadata){
    char* rawRegister =  this.file.getRawRegister(SPACE_MAP_NUMBER);

    //Analize the register to find free space
}

Persistance::findRegisterAddress(int nodeId){
    char* rawRegister = this.file.getRegister(ID_REGISTER_MAP_NUMBER);

    //Analize the register to find the number where the node is in

}
