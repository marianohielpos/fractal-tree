#include "./Register.hpp"
#include "./LeafNode.hpp"

#include <string>
#include <stdint.h>
#include <vector>
#include <map>
#include <cstring>


LeafNode::LeafNode(){}

uint32_t LeafNode::getType(){
    return 1;
}

Register LeafNode::getRegister(uint32_t id){
    return this->registers[id];
}

bool LeafNode::getStream(char* buffer, uint32_t size){
    std::cout << "Serializing node" << std::endl;

    uint32_t offset = 0;
    char oneChar = 0x01;

    std::map<uint32_t,Register>::iterator iterator = this->registers.begin();

    if( !buffer || this->getSize() > size){
        std::cout << "Warning buffer is not capable" << std::endl;
        return false;
    }

    //Inner node starts with a one
    memcpy(buffer, &oneChar, sizeof(char));

    offset += 1;

    uint32_t numberOfRegisters = this->registers.size();

    //Number of registers
    memcpy(buffer + offset, &numberOfRegisters, sizeof(numberOfRegisters));

    offset += sizeof(numberOfRegisters);

    for (; iterator != this->registers.end(); ++iterator){

        iterator->second.getStream(buffer + offset, iterator->second.getSize() );

        offset += iterator->second.getSize();

    }

    return true;

}

uint32_t LeafNode::getSize(){
    //First char indicating type and 4 for the size
    uint32_t size = 5;

    std::map<uint32_t,Register>::iterator iterator = this->registers.begin();

    for (; iterator != this->registers.end(); ++iterator){
        size += iterator->second.getSize();
    }

    return size;
}

bool LeafNode::insertRegister(Register& _register){

    this->registers[_register.getId()] = Register(_register);
    return true;
}

LeafNode::LeafNode(const char* byteStream)
    : Node()
    {
    //Avoid the first byte
    uint32_t offset = 1;
    uint32_t numberOfRegisters = 0;

    memcpy(&numberOfRegisters, byteStream + offset, sizeof(uint32_t));

    offset += sizeof(uint32_t);

    for(uint32_t j = 0; j < numberOfRegisters; j++ ){
        //Workaround for now. Skips the id and code of a node to search por the ending

        Register _register = Register(&byteStream[offset]);

        offset += _register.getSize();

        this->registers[_register.getId()] = _register;
    }

}

LeafNode::~LeafNode(){}
