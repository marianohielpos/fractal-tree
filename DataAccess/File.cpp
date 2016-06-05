/* File description:
*  First block: Metadata. 1 byte per node
*  Other blocks: Data
*  Free space control: Bytemap, representing the percentage of use of each block
*  Each register is finished with a EOF
*/
#include "File.hpp"

#include <iostream>
#include <fstream>

#define BITS_PER_BYTE 4

File::File(std::string pathToFile, size_t registerSize){

    this->registerSize = registerSize;
    this->pathToFile = std::string(pathToFile);

    if ( !std::ifstream(this->pathToFile.c_str()))
    {
        this->initializeControlSector(0);
    }
}

bool File::initializeControlSector(size_t zone){
    std::fstream myfile;
    myfile.open(this->pathToFile.c_str(), std::ios::out | std::ios::in | std::ios::binary);

    if( zone != 0){
        myfile.seekg(this->getMappingZonePosition(zone));
    }

    if( !myfile ){
        return false;
    }
    for(size_t counter = 0; counter < this->registerSize; counter++){
        myfile.put((char)0);
    }

    myfile.close();

    return true;
}

size_t File::getNodePosition(size_t id){
    size_t fileSize = this->getFileSize();

    char* block;

    size_t numberOfZones = fileSize / ( this->registerSize / BITS_PER_BYTE );

    for(int i = 0;i < numberOfZones; i++){
        block = this->getZoneControlBlock(i);
        for(int j = 0; j <= this->registerSize; j += BITS_PER_BYTE){

            //Converion from char to size_t
            size_t x = (block[j] << 24) | (block[j + 1] << 16) | (block[j + 2] << 8) | block[j + 3];

            if( x == id ){
                return (this->getMappingZonePosition(i) + j * BITS_PER_BYTE);
            }
        }
    }
    return 0;
}

char* File::getZoneControlBlock(size_t zone){
    size_t blockPosition = this->getMappingZonePosition(zone);

    return this->getBlock(blockPosition);
}

char* File::getBlock(size_t blockPosition){

    char* memblock;
    std::fstream myfile;

    myfile.open(this->pathToFile.c_str(), std::ios::out | std::ios::in | std::ios::binary);

    if ( !myfile.is_open() ) {
      return NULL;
    }

    memblock = new char [this->registerSize];
    myfile.seekg((blockPosition));
    myfile.read(memblock, this->registerSize);
    myfile.close();

    return memblock;
}

size_t File::getMappingZonePosition(size_t zone){
    return (zone * (this->registerSize / BITS_PER_BYTE) + zone);
}

size_t File::getFileSize(){
    std::streampos begin, end;
    std::ifstream myfile(this->pathToFile.c_str(), std::ios::binary);

    begin = myfile.tellg();
    myfile.seekg(0, std::ios::end);
    end = myfile.tellg();

    myfile.close();

    return (size_t)(end-begin);
}

size_t File::getFreeSpaceDirection(){

    return this->getNodePosition(0);

}

Node* File::getNode(size_t id){

    size_t blockPosition = this->getNodePosition(id);

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

    size_t blockPosition = getNodePosition(*node->getId());

    if( blockPosition == 0 ){
        blockPosition = this->getFreeSpaceDirection();
    }

    myfile.open(this->pathToFile.c_str(), std::ios::out | std::ios::in | std::ios::binary);

    if ( !myfile.is_open() ) {
      return NULL;
    }

    myfile.seekg(blockPosition);

    myfile.write(node->getStream(),node->getSize() );

	return true;
}
