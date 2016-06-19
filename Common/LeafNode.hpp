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

    bool insertRegister(Register& _register);

    Register getRegister(uint32_t id);

    bool getStream(char* buffer, uint32_t size);

    uint32_t getSize();

    LeafNode();

    LeafNode(const char* byteStream);

    ~LeafNode(void);

    uint32_t getType();


protected:

private:
    std::map <uint32_t,Register> registers;
};

#endif // _LEAF_NODE_H_
