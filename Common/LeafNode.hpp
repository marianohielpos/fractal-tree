#include "./Node.hpp"

#include <string>
#include <stdint.h>
#include <vector>

#ifndef _LEAF_NODE_H_
#define _LEAF_NODE_H_

#include "Register.hpp"

class LeafNode : public Node
{
public:

    void insertRegister(uint32_t place, Register& registers);

    bool insertRegister(Register& registers);

    Register getRegister(uint32_t place);

    bool getStream(char* buffer, uint32_t size);

    uint32_t getSize();

    LeafNode();

    LeafNode(const char* byteStream);

    ~LeafNode(void);

    uint32_t getType();


protected:

private:
    std::vector<Register> registers;
    std::vector<uint32_t> offsets;
};

#endif // _LEAF_NODE_H_
