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

    bool initializeControlSector(uint32_t controlSectorNumber);

    uint32_t getNodePosition(uint32_t id);

    void getBlock(uint32_t blockPosition, char* memblock);

    bool setToCeroSector(uint32_t sector);

    uint32_t getFileSize();

    uint32_t getFreeSpaceDirection();

    bool registersId(uint32_t blockPosition, uint32_t id);

    Node* getNode(uint32_t offset);

    bool setControlPosition(uint32_t position, bool setToCero);

    uint32_t saveNode(Node* node);

    bool saveNode(Node* node, uint32_t offset);

    bool deleteNode(uint32_t id);

    uint32_t getMappingZone(uint32_t zone);

    File(const char* pathToFile, uint32_t blockSize);

    ~File();

protected:

private:

    bool checkFileExistance(const char* pathToFile);

    uint32_t blockSize;
    std::string pathToFile;
    std::fstream openFile;

    NodeFactory factory;

};

#endif // _FILE_H_
