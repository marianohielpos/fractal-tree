#include "./Node.hpp"

#include <string>
#include <stdint.h>
#include <vector>
#include <map>

#ifndef _INNER_NODE_H_
#define _INNER_NODE_H_

#define FRACTAL_COHEFICIENT 8

class InnerNode: public Node
{
public:

    void insertReference(uint32_t nodeId, uint32_t offset);

    void deleteReference(uint32_t nodeId);

    uint32_t getReference(uint32_t nodeId);

    bool getStream(char* buffer, uint32_t size);

    const char* getBuffer();

    void insertInBuffer(const char* _register);

    uint32_t getSize();

    InnerNode();

    InnerNode(const char* byteStream);

    ~InnerNode(void);

    uint32_t getType();


protected:

private:
    std::map <uint32_t,uint32_t> references;
    std::string buffer;
};

#endif // _INNER_NODE_H_
