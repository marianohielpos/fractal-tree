#include <string>
#include <stdint.h>
#include <vector>

#ifndef _NODE_H_
#define _NODE_H_

#include "Register.hpp"
#define FRACTAL_COHEFICIENT 8

class Node
{
public:

    virtual bool getStream(char* buffer, uint32_t size) = 0;

    virtual uint32_t getSize() = 0;

    virtual uint32_t getType() = 0;

    Node(){};

    ~Node(){};

protected:

private:

};

#endif // _NODE_H_
