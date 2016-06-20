#include "./Node.hpp"
#include "Register.hpp"

#include <string>
#include <stdint.h>
#include <vector>
#include <map>
#include <iostream>


#ifndef _LEAF_NODE_H_
#define _LEAF_NODE_H_
class LeafNode : public Node
{
public:

    bool getStream(char* buffer, uint32_t size);

    uint32_t getSize();

    uint32_t getMin();

    LeafNode();

    LeafNode(const char* byteStream);

    ~LeafNode(void);

    uint32_t getType();


protected:

private:
};

#endif // _LEAF_NODE_H_
