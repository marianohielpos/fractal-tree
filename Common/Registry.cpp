/*
*   The responsability of releasing the dinamic memory of the node is given
*   to the one who is the last one that uses the node.
*
*/

#include "Registry.hpp"
#include <string>
#include <iostream>
#include <sstream>

#define FRACTAL_COHEFICIENT


uint32_t* Registry::getId(){
    return this->id;
}

std::string* Registry::getCode(){
    return this->code;
}

std::string* Registry::getDescription(){
    return this->description;
}

const char* Registry::getStream(){
    std::stringstream ss;
    unsigned char end = 255;
    ss << *this->getDescription() << *this->getCode() << end ;
    const char* p = ss.str().c_str();
    return p;
}

void Registry::setCode(const char* code){
    delete this->code;
    this->code = new std::string(code);
}

void Registry::setDescription(const char* description){
    delete this->description;
    this->description = new std::string(description);
}

void Registry::setId(int id){
    delete this->id;
    this->id = new uint32_t(id);
}

Registry::Registry(uint32_t id, const char* code, const char* description){
    this->id = new uint32_t(id);
    this->code = new std::string(code);
    this->description = new std::string(description);
}

Registry::Registry(char* biteString){
    //TODO
}

uint32_t Registry::getSize(){
    return (sizeof(*this->code) + sizeof(*this->description) + 1);
}

Registry::~Registry(void){
    delete this->id;
    delete this->code;
    delete this->description;
}
