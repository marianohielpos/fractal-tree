#include <map>
#include "./Node.hpp"
#include <cstring>


void Node::serializeRegisters(char* buffer){

    uint32_t numberOfRegisters = this->registers.size();
    uint32_t offset = 0;

    std::map<uint32_t,Register>::iterator iterator = this->registers.begin();

    memcpy(buffer + offset, &numberOfRegisters, sizeof(numberOfRegisters));

    offset += sizeof(numberOfRegisters);

    for (; iterator != this->registers.end(); ++iterator){

        iterator->second.getStream(buffer + offset, iterator->second.getSize() );

        offset += iterator->second.getSize();

    }
}

void Node::deSerializeRegisters(const char* byteStream){
    uint32_t numberOfRegisters = 0;
    uint32_t offset = 0;

    memcpy(&numberOfRegisters, byteStream + offset, sizeof(uint32_t));

    offset += sizeof(uint32_t);

    for(uint32_t j = 0; j < numberOfRegisters; j++ ){

        Register _register = Register(&byteStream[offset]);

        offset += _register.getSize();

        this->registers[_register.getId()] = _register;
    }
}
