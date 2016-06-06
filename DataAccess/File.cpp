/* File description:
*  First block: Metadata. 1 byte per node
*  Other blocks: Data
*  Free space control: Bytemap, representing the percentage of use of each block
*  Each register is finished with a EOF
*/
#include "File.hpp"
#include "../Common/Node.hpp"
#include <iostream>
#include <fstream>
#include <string.h>

File::File(std::string pathToFile, uint32_t registerSize){

    this->registerSize = registerSize;
    this->pathToFile = std::string(pathToFile);

    if ( !std::ifstream(this->pathToFile.c_str()))
    {
        this->initializeControlSector(0);
    }
    std::cout << "Finished\n";
}

bool File::initializeControlSector(uint32_t block){

    std::cout << "Initializing\n";
    std::fstream myfile;
    myfile.open(this->pathToFile.c_str(), std::ios::out | std::ios::in | std::ios::binary | std::ios::app);

    std::cout << "Chequing block\n";
    if( block != 0){
        myfile.seekg(this->getMappingZonePosition(block));
    }

    std::cout << "Chequing if file is open\n";
    if( !myfile.is_open() ){
        return false;
    }

    std::cout << "Setting to cero\n";
    for(uint32_t counter = 0; counter < this->registerSize; counter++){
        myfile.put(0);
    }

    std::cout << "Closing file\n";
    myfile.close();

    std::cout << "Return\n";
    return true;
}

uint32_t File::getNodePosition(uint32_t id){
    uint32_t fileSize = this->getFileSize();

    char* block;

    uint32_t number;

    uint32_t numberOfZones = fileSize % ( this->registerSize / sizeof(uint32_t) ) + 1;

    for(uint32_t i = 0;i < numberOfZones; i++){
        block = this->getZoneControlBlock(i);
        for(uint32_t j = 0; j < this->registerSize; j += 4){
            //Converion from char to uint32_t
            memcpy(&number, block + j, sizeof(uint32_t));
            if( number == id ){
                std::cout << "Find: " << id << "  " << j << " " <<((j/4 + i + 1) * this->registerSize) << std::endl;
                return ((j/4 + i + 1) * this->registerSize);
            }
        }
    }
    return 0;
}

uint32_t File::getControlZoneNumber(uint32_t blockPosition){
    return blockPosition/this->registerSize -1;
}

char* File::getZoneControlBlock(uint32_t zone){
    uint32_t blockPosition = this->getMappingZonePosition(zone);
    std::cout << "mappingzone  " << blockPosition   << std::endl;

    return this->getBlock(blockPosition);
}

char* File::getBlock(uint32_t blockPosition){

    char* memblock;
    std::fstream myfile;

    myfile.open(this->pathToFile.c_str(), std::ios::out | std::ios::in | std::ios::binary);

    if ( !myfile.is_open() ) {
      return NULL;
    }

    memblock = new char [this->registerSize];
    myfile.seekg(0);
    myfile.read(memblock, this->registerSize);
    myfile.close();

    return memblock;
}

uint32_t File::getMappingZonePosition(uint32_t zone){
    return (zone * (this->registerSize / sizeof(uint32_t)) + zone);
}

uint32_t File::getFileSize(){
    std::streampos begin, end;
    std::ifstream myfile(this->pathToFile.c_str(), std::ios::binary);

    begin = myfile.tellg();
    myfile.seekg(0, std::ios::end);
    end = myfile.tellg();

    myfile.close();

    return (uint32_t)(end-begin);
}

uint32_t File::getFreeSpaceDirection(){

    return this->getNodePosition(0);

}

Node* File::getNode(uint32_t id){

    uint32_t blockPosition = this->getNodePosition(id);

    if( blockPosition == 0 ){
        return NULL;
    }

    char* memblock;

    memblock = this->getBlock(blockPosition);

    return new Node(memblock);
}

bool File::saveNode(Node* node){

    std::fstream myfile;

    if( node->getSize() > this->registerSize ){
        return false;
    }

    uint32_t blockPosition = getNodePosition(*node->getId());

    if( blockPosition == 0 ){
        blockPosition = this->getFreeSpaceDirection();
    }

    std::cout << "Node position: " << blockPosition << std::endl;


    myfile.open(this->pathToFile.c_str(), std::ios::out | std::ios::in | std::ios::binary);

    if ( !myfile.is_open() ) {
      return NULL;
    }

    myfile.seekg(blockPosition);

    myfile.write(node->getStream(), node->getSize() );

    for(uint32_t i = node->getSize(); i < this->registerSize; i++){
        myfile.put(0);
    }

    if( !this->registerId(blockPosition, *node->getId()) ) {
        return false;
    }

	return true;
}

bool File::registerId(uint32_t blockPosition, uint32_t id){
    std::fstream myfile;

    std::cout << "blockPosition: " << blockPosition << std::endl;

    uint32_t controlZone = getControlZoneNumber(blockPosition);

    std::cout << "controlZone: " << controlZone << std::endl;

    myfile.open(this->pathToFile.c_str(), std::ios::out | std::ios::in | std::ios::binary);

    if( !myfile.is_open() ){
        return false;
    }

    myfile.seekg(controlZone);

    char stream[255] = "";

    memcpy(stream, &id, sizeof(id));

    myfile.write(stream, sizeof(id));

    myfile.close();

    return true;
}

bool File::setToCeroPosition(uint32_t position){
    std::fstream myfile;
    myfile.open(this->pathToFile.c_str(), std::ios::out | std::ios::in | std::ios::binary);

    if( !myfile ){
        return false;
    }

    myfile.seekg(this->getMappingZonePosition(position));

    for(uint32_t counter = 0; counter < sizeof(uint32_t); counter++){
        myfile.put((char)0);
    }

    myfile.close();

    return true;

}

bool File::deleteNode(uint32_t id){
    uint32_t fileSize = this->getFileSize();

    char* block;

    uint32_t numberOfZones = fileSize / ( this->registerSize / sizeof(uint32_t) );

    for(uint32_t i = 0;i < numberOfZones; i++){
        block = this->getZoneControlBlock(i);
        for(uint32_t j = 0; j <= this->registerSize; j += sizeof(uint32_t)){

            //Converion from char to uint32_t
            uint32_t x = (block[j] << 24) | (block[j + 1] << 16) | (block[j + 2] << 8) | block[j + 3];

            if( x == id ){
                uint32_t pointerPosition = this->getMappingZonePosition(i) + j;
                return setToCeroPosition(pointerPosition);
            }
        }
    }
    return false;

}
