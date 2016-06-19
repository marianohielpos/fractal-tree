#include <string>
#include <stdint.h>
#include <vector>
#include <map>


#ifndef _NODE_H_
#define _NODE_H_

#include "Register.hpp"

class Node
{
public:

    virtual bool getStream(char* buffer, uint32_t size) = 0;

    virtual uint32_t getSize() = 0;

    virtual uint32_t getType() = 0;

    Node(){};

    virtual ~Node(){};

protected:

    void serializeRegisters(char* buffer);
    void deSerializeRegisters(const char* byteStream);

    std::map <uint32_t,Register> registers;

private:
};

#endif // _NODE_H_
