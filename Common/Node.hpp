#include <string>
#include <stdint.h>

#ifndef _NODE_H_
#define _NODE_H_

#include "Register.hpp"


class Node
{
public:

    void setRegister(Register* _register);

    Register* getRegister(uint32_t* id);

    const char* getStream();

    uint32_t getSize();

    Node();

    Node(char* biteStream);

    ~Node(void);

protected:

private:
    Register* _register;
};

#endif // _NODE_H_
