#include "Register.hpp"
#include <string>
#include <iostream>
#include <sstream>
#include <cstring>

uint32_t Register::getId(){
    return this->id;
}

const char* Register::getCode(){
    return this->code.c_str() + '\0';
}

const char* Register::getDescription(){
    return this->description.c_str() + '\0';
}

bool Register::getStream(char* buffer, uint32_t size){

    if( !buffer || this->getSize() > size){
        return false;
    }

    uint32_t offset = 0;

    memcpy(buffer, &this->id, sizeof(uint32_t));

    offset += sizeof(uint32_t);

    strcpy(buffer + offset, this->getCode());

    //Plus null character
    offset += strlen(this->getCode()) + 1;

    strcpy(buffer + offset, this->getDescription());

    return true;
}

void Register::setCode(const char* code){
    this->code = std::string(code);
}

void Register::setDescription(const char* description){
    this->description = std::string(description);
}

void Register::setId(uint32_t id){
    this->id = id;
}

Register::Register(uint32_t id, const char* code, const char* description){
    this->id = id;
    this->code = std::string(code);
    this->description = std::string(description);
}

Register::Register(const char* byteString){

    uint32_t offset = 0;

    memcpy(&this->id, byteString, sizeof(uint32_t));

    offset += sizeof(uint32_t);
    uint32_t i = offset;

    for(; (char)byteString[i] != '\0' ; ++i);

    this->code = std::string(&byteString[offset], i - offset);

    i += 1;

    offset = i;

    for(; (char)byteString[i] != '\0' ; ++i);

    std::cout << i << std::endl;

    this->description = std::string(&byteString[offset], i);

}

Register::Register(const Register& registers)
    : id(registers.id),
    code(registers.code),
    description(registers.description){}

uint32_t Register::getSize(){
    //Plust two because of the '\0' in the strings
    return (sizeof(this->id) + strlen(this->code.c_str()) + strlen(this->description.c_str()) + 2);
}

Register::~Register(void){
}

Register::Register(){
}
