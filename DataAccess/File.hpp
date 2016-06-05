#ifndef _FILE_H_
#define _FILE_H_

#include <iostream>
#include "../Common/Node.hpp"


class File
{
public:

    bool initializeControlSector(size_t zone);

    size_t getNodePosition(size_t id);

    char* getZoneControlBlock(size_t zone);

    char* getBlock(size_t blockPosition);

    size_t getMappingZonePosition(size_t zone);

    size_t getFileSize();

    size_t getFreeSpaceDirection();

    Node* getNode(size_t id);

    bool setToCeroPosition(size_t position);

    bool saveNode(Node* node);

    bool deleteNode(size_t id);

    size_t getMappingZone(size_t zone);

    File(std::string pathToFile, size_t registerSize);

protected:

private:
    size_t registerSize;
    std::string pathToFile;
};

#endif // _FILE_H_
