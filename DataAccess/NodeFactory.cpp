#include "../Common/Node.hpp"
#include "../Common/InnerNode.hpp"
#include "../Common/LeafNode.hpp"
#include "./NodeFactory.hpp"
#include <iostream>
#include <stdio.h>
#include <string.h>


Node* NodeFactory::buildNode(const char* charStream){

    char type;

    memcpy(&type, charStream, sizeof(char));

    switch (type) {
        case 0:
            std::cout << "Making an InnerNode" << std::endl;
            return (Node*) new InnerNode(charStream);
            break;
        case 1:
            //return (Node*) new LeafNode(charStream);
            break;
    }

    std::cout << "Something went wrong " << (uint32_t)type << std::endl;
    return NULL;
}
