#ifndef _FILE_H_
#define _FILE_H_

#include <iostream>
#include "../Common/Node.hpp"
#include "./NodeFactory.hpp"
#include <stdint.h>
#include <fstream>
#include <sys/stat.h>

class File
{
public:

    bool setToCeroSector(uint32_t sector);

    uint32_t getFileSize();

    Node* getNode(uint32_t number);

    uint32_t saveNode(Node* node);

    bool saveNode(Node* node, uint32_t offset);

    bool deleteNode(uint32_t id);

    File(const char* pathToFile, uint32_t blockSize);

    ~File();

protected:

private:

    uint32_t getMappingZone(uint32_t zone);

    bool checkFileExistance(const char* pathToFile);

    void getBlock(uint32_t blockPosition, char* memblock);

    bool setControlPosition(uint32_t position, bool setToCero);

    uint32_t getFreeSpaceDirection();

    bool initializeControlSector(uint32_t controlSectorNumber);

    NodeFactory factory;
    uint32_t blockSize;
    std::string pathToFile;
    std::fstream openFile;

};

#endif // _FILE_H_
