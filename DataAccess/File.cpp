/* File description:
*  First block: Metadata. 1 byte per node
*  Other blocks: Data
*  Free space control: Bytemap, representing the percentage of use of each block
*  Each _register is finished with a EOF
*/
#include "File.hpp"
#include "../Common/Node.hpp"
#include <iostream>
#include <fstream>
#include <string.h>

File::File(std::string pathToFile, uint32_t blockSize){

    this->blockSize = blockSize;
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
    for(uint32_t counter = 0; counter < this->blockSize; counter++){
        myfile.put(0);
    }

    std::cout << "Closing file\n";
    myfile.close();

    std::cout << "Return\n";
    return true;
}


uint32_t File::getControlZoneNumber(uint32_t blockPosition){
    return (blockPosition/this->blockSize -1);
}

char* File::getZoneControlBlock(uint32_t zone){
    uint32_t blockPosition = this->getMappingZonePosition(zone);

    return this->getBlock(blockPosition);
}

char* File::getBlock(uint32_t blockPosition){

    char* memblock;
    std::fstream myfile;

    uint32_t absoluteBlockPosition = blockPosition * this->blockSize;

    myfile.open(this->pathToFile.c_str(), std::ios::out | std::ios::in | std::ios::binary);

    if ( !myfile.is_open() ) {
      return NULL;
    }

    memblock = new char [this->blockSize];
    myfile.seekg(absoluteBlockPosition);
    myfile.read(memblock, this->blockSize);
    myfile.close();

    return memblock;
}

uint32_t File::getMappingZonePosition(uint32_t zone){
    return (zone * (this->blockSize + zone));
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

    const char* block = this->getBlock(0);

    char character;

    for( uint32_t i = 0; i < this->blockSize; i++){
        character = block[i];
        for( uint32_t j = 0; j < 8; j++ ){
            
            if ( !(character & 0x01) ) {
                return (i * 8 + j);
            }

            character = character >> 1;
        }
    }

    return 0;

}

Node* File::getNode(uint32_t offset){

    char* memblock;

    memblock = this->getBlock(offset);

    Node* node = new Node(memblock);

    delete memblock;

    return node;
}

uint32_t File::saveNode(Node* node){

    uint32_t positionInControlZone = this->getFreeSpaceDirection();

    unsigned long long blockPosition = (positionInControlZone + 1) * this->blockSize;

    std::cout << "Block position found: " << blockPosition << std::endl;

    std::fstream myfile;

    myfile.open(this->pathToFile.c_str(), std::ios::out | std::ios::in | std::ios::binary);

    if ( !myfile.is_open() ) {
      return 0;
    }

    this->setControlPosition(positionInControlZone, false);

    myfile.seekg(blockPosition);

    myfile.write(node->getStream(), node->getSize() );

    return (positionInControlZone + 1);
}



bool File::saveNode(Node* node, uint32_t offset){

    std::fstream myfile;

    uint32_t blockPosition = offset * this->blockSize;

    myfile.open(this->pathToFile.c_str(), std::ios::out | std::ios::in | std::ios::binary);

    if ( !myfile.is_open() ) {
      return NULL;
    }

    myfile.seekg(blockPosition);

    myfile.write(node->getStream(), node->getSize() );

	return true;
}

bool File::setControlPosition(uint32_t positionInControlZone, bool setToCero){

    std::fstream myfile;

    myfile.open(this->pathToFile.c_str(), std::ios::out | std::ios::in | std::ios::binary);

    if( !myfile ){
        return false;
    }

    myfile.seekg(positionInControlZone / 8);

    char controlChar = myfile.get();

    //Set to cero a position
    char register ceroMask = 0xFE;
    //Set to one a position
    char register oneMask = 0x01;

    for(uint32_t i = 0; i < positionInControlZone % 8; i++){
        ceroMask = ceroMask << (positionInControlZone % 8);
        oneMask = (oneMask << (positionInControlZone % 8)) | 0x01;
    }

    if( setToCero ){
        controlChar = controlChar & ceroMask;
    }
    else{
        controlChar = controlChar | oneMask;
    }

    myfile.seekg(positionInControlZone / 8);

    myfile.put(controlChar);

    myfile.close();

    return true;

}

bool File::deleteNode(uint32_t offset){
    return this->setControlPosition(offset -1, false);
}
