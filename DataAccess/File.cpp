/* File description:
*  First block: Metadata. 1 byte per node
*  Other blocks: Data
*  Free space control: Bytemap, representing the percentage of use of each block
*  Each registers is finished with a EOF
*/
#include "File.hpp"
#include "../Common/InnerNode.hpp"
#include "../Common/LeafNode.hpp"
#include "./NodeFactory.hpp"
#include <iostream>
#include <fstream>
#include <string.h>
#include <sys/stat.h>


File::File(const char* pathToFile, uint32_t blockSize){

    this->blockSize = blockSize;
    this->pathToFile = std::string(pathToFile);

    this->factory = NodeFactory();

    if ( !this->checkFileExistance(pathToFile))
    {
        std::cout << "Initializing file" << std::endl;
        this->openFile.open(this->pathToFile.c_str(), std::ios::out | std::ios::in | std::ios::binary | std::ios::trunc);
        if ( (this->openFile.rdstate() & std::ifstream::failbit ) != 0 )
            std::cerr << "Error opening file \n";
        this->initializeControlSector(0);
    }
    else{
        std::cout << "Opening existing file" << std::endl;
        this->openFile.open(this->pathToFile.c_str(), std::ios::out | std::ios::in | std::ios::binary);
        if ( (this->openFile.rdstate() & std::ifstream::failbit ) != 0 )
            std::cerr << "Error opening file \n";

    }
}

File::~File(){
    this->openFile.close();
}


bool File::checkFileExistance(const char* pathToFile){
  struct stat buffer;

  return (stat (pathToFile, &buffer)) == 0;
}


bool File::initializeControlSector(uint32_t controlSectorNumber){
    return this->setToCeroSector(this->getMappingZonePosition(controlSectorNumber));
}

bool File::setToCeroSector(uint32_t sectorOffset){

    this->openFile.seekg(sectorOffset);

    std::cout << "Setting to cero\n";
    for(uint32_t counter = 0; counter < this->blockSize; counter++){
        this->openFile.put(0);
    }

    return true;
}


uint32_t File::getControlZoneNumber(uint32_t blockPosition){
    return (blockPosition/this->blockSize -1);
}

char* File::getZoneControlBlock(uint32_t controlSectorNumber){
    return this->getBlock(this->getMappingZonePosition(controlSectorNumber));
}

char* File::getBlock(uint32_t blockPosition){

    char* memblock;

    uint32_t absoluteBlockPosition = blockPosition * this->blockSize;

    memblock = new char [this->blockSize];
    this->openFile.seekg(absoluteBlockPosition);
    this->openFile.read(memblock, this->blockSize);

    return memblock;
}

uint32_t File::getMappingZonePosition(uint32_t zone){
    return (zone * (this->blockSize + zone));
}

uint32_t File::getFileSize(){
    std::streampos begin, end;

    this->openFile.seekg(0);
    begin = this->openFile.tellg();
    this->openFile.seekg(0, std::ios::end);
    end = this->openFile.tellg();

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

    Node* node = this->factory.buildNode(memblock);

    delete memblock;

    return node;
}

uint32_t File::saveNode(Node* node){

    uint32_t positionInControlZone = this->getFreeSpaceDirection();

    std::cout << "position in control zone: " << positionInControlZone << std::endl;

    uint32_t blockPosition = (positionInControlZone + 1) * this->blockSize;

    std::cout << "Block position found: " << blockPosition << std::endl;

    this->setControlPosition(positionInControlZone, false);

    this->openFile.seekg(blockPosition);

    uint32_t nodeSize = node->getSize();

    char buffer[nodeSize];

    std::cout << "Node size: " << node->getSize() << std::endl;
    std::cout << "Node type: " << node->getType() << std::endl;


    node->getStream(buffer, nodeSize);

    this->openFile.write(buffer, nodeSize );

    return (positionInControlZone + 1);
}



bool File::saveNode(Node* node, uint32_t offset){

    uint32_t blockPosition = offset * this->blockSize;

    this->openFile.seekg(blockPosition);

    char buffer[node->getSize()];

    node->getStream(buffer, node->getSize());

    this->openFile.write(buffer, node->getSize() );

	return true;
}

bool File::setControlPosition(uint32_t positionInControlZone, bool setToCero){

    this->openFile.seekg(positionInControlZone / 8);

    char controlChar = this->openFile.get();

    this->openFile.seekg(positionInControlZone / 8);

    //Set to cero a position
    char register ceroMask = 0xFE;
    //Set to one a position
    char register oneMask = 0x01;

    for(uint32_t i = 0; i < positionInControlZone % 8; i++){
        ceroMask = (ceroMask << 1) | 0x01;
        oneMask = oneMask << 1;
    }

    if( setToCero ){
        controlChar = controlChar & ceroMask;
    }
    else{
        controlChar = controlChar | oneMask;
    }

    std::cout << "Control char " << (uint32_t)controlChar << std::endl;
    std::cout << "Position " << (uint32_t)positionInControlZone << std::endl;

    this->openFile.put(controlChar);

    return true;

}

bool File::deleteNode(uint32_t offset){
    return this->setControlPosition(offset, true) && this->setToCeroSector(offset);
}
