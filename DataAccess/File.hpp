#ifndef _FILE_H_
#define _FILE_H_

#include <iostream>
#include "../Common/Node.hpp"
#include <stdint.h>


class File
{
public:

    void getZoneValue(uint32_t zone);

    bool initializeControlSector(uint32_t zone);

    uint32_t getNodePosition(uint32_t id);

    char* getZoneControlBlock(uint32_t zone);

    char* getBlock(uint32_t blockPosition);

    uint32_t getMappingZonePosition(uint32_t zone);

    uint32_t getFileSize();

    uint32_t getFreeSpaceDirection();

    bool registerId(uint32_t blockPosition, uint32_t id);

    uint32_t getControlZoneNumber(uint32_t blockPosition);

    Node* getNode(uint32_t id);

    bool setToCeroPosition(uint32_t position);

    bool saveNode(Node* node);

    bool deleteNode(uint32_t id);

    uint32_t getMappingZone(uint32_t zone);

    File(std::string pathToFile, uint32_t registerSize);

protected:

private:
    uint32_t registerSize;
    std::string pathToFile;
};

#endif // _FILE_H_
