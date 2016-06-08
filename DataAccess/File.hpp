#ifndef _FILE_H_
#define _FILE_H_

#include <iostream>
#include "../Common/Node.hpp"
#include <stdint.h>


class File
{
public:

    bool initializeControlSector(uint32_t zone);

    uint32_t getNodePosition(uint32_t id);

    char* getZoneControlBlock(uint32_t zone);

    char* getBlock(uint32_t blockPosition);

    uint32_t getMappingZonePosition(uint32_t zone);

    uint32_t getFileSize();

    uint32_t getFreeSpaceDirection();

    bool _registerId(uint32_t blockPosition, uint32_t id);

    uint32_t getControlZoneNumber(uint32_t blockPosition);

    Node* getNode(uint32_t offset);

    bool setControlPosition(uint32_t position, bool setToCero);

    uint32_t saveNode(Node* node);

    bool saveNode(Node* node, uint32_t offset);

    bool deleteNode(uint32_t id);

    uint32_t getMappingZone(uint32_t zone);

    File(std::string pathToFile, uint32_t blockSize);

protected:

private:
    uint32_t blockSize;
    std::string pathToFile;
};

#endif // _FILE_H_
