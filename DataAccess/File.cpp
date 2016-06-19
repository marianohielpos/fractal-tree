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
    return this->setToCeroSector(0);
}

bool File::setToCeroSector(uint32_t blockPosition){

    this->openFile.seekg(blockPosition * this->blockSize);

    std::cout << "Setting to cero\n";
    for(uint32_t counter = 0; counter < this->blockSize; counter++){
        this->openFile.put(0);
    }

    return true;
}


void File::getBlock(uint32_t blockPosition, char* memblock){

    uint32_t absoluteBlockPosition = blockPosition * this->blockSize;

    this->openFile.seekg(absoluteBlockPosition);
    this->openFile.read(memblock, this->blockSize);

    return;
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

    char block[this->blockSize];

    this->getBlock(0, block);

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
    this->openFile.clear();

    char memblock[this->blockSize];

    this->getBlock(offset, memblock);

    Node* node = this->factory.buildNode(memblock);

    return node;
}

uint32_t File::saveNode(Node* node){
    this->openFile.clear();
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

    if( node->getSize() > this->blockSize ){
        return false;
    }
    
    uint32_t blockPosition = offset * this->blockSize;

    this->openFile.seekg(blockPosition);

    char buffer[node->getSize()];

    node->getStream(buffer, node->getSize());

    this->openFile.write(buffer, node->getSize() );

	return true;
}

bool File::setControlPosition(uint32_t positionInControlZone, bool setToCero){

    this->openFile.clear();
    this->openFile.seekg(positionInControlZone / 8);

    char controlChar = this->openFile.get();

    //Set to cero a position
    char ceroMask = 0xFE;
    //Set to one a position
    char oneMask = 0x01;

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

    this->openFile.seekg(positionInControlZone / 8);

    this->openFile.put(controlChar);

    return true;
}

bool File::deleteNode(uint32_t blockNumber){
    std::cout << "Deleting node " << blockNumber << std::endl;
    this->setControlPosition(blockNumber - 1, true);
    this->setToCeroSector(blockNumber);
    return true;
}
