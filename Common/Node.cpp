#include <map>
#include "./Node.hpp"
#include <cstring>
#include <iostream>

bool Node::removeRegisters(){
    std::map <uint32_t,Register> registers;
    this->registers = registers;
    return true;
}

std::map<uint32_t,Register>* Node::getRegisters(void){
    return &this->registers;
}

Register* Node::getRegister(uint32_t id){
    return &this->registers.lower_bound(id)->second;
}

bool Node::exists(uint32_t id){
    if( this->registers.find(id) == this->registers.end() ){
        return false;
    }
    return true;
}

bool Node::removeRegister(uint32_t id){
    if( this->registers.find(id) == this->registers.end() ){
        return false;
    }
    this->registers.erase(id);
    return true;
}

bool Node::insertRegister(Register* _register){

    this->registers[_register->getId()] = Register(*_register);
    return true;
}


void Node::serializeRegisters(char* buffer){

    uint32_t numberOfRegisters = this->registers.size();
    uint32_t offset = 0;

    std::map<uint32_t,Register>::iterator iterator = this->registers.begin();

    std::cout << "serializeRegisters" << std::endl;
    std::cout << "Number of registers " << numberOfRegisters << std::endl;

    memcpy(buffer, &numberOfRegisters, sizeof(numberOfRegisters));

    offset += sizeof(numberOfRegisters);

    for (; iterator != this->registers.end(); ++iterator){

        iterator->second.getStream(buffer + offset, iterator->second.getSize() );

        offset += iterator->second.getSize();

    }
}

void Node::deSerializeRegisters(const char* byteStream){
    uint32_t numberOfRegisters = 0;
    uint32_t offset = 0;

    std::cout << "deSerializeRegisters" << std::endl;

    memcpy(&numberOfRegisters, byteStream + offset, sizeof(uint32_t));

    std::cout << "Number of refgisters: " << numberOfRegisters << std::endl;

    offset += sizeof(uint32_t);

    for(uint32_t j = 0; j < numberOfRegisters; j++ ){

        Register _register = Register(&byteStream[offset]);

        std::cout << "Register id: " << _register.getId() << std::endl;

        offset += _register.getSize();

        this->registers[_register.getId()] = _register;
    }
}
