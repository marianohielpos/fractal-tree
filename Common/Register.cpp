/*
*   The responsability of releasing the dinamic memory of the node is given
*   to the one who is the last one that uses the node.
*
*/

#include "Register.hpp"
#include <string>
#include <iostream>
#include <sstream>

#define FRACTAL_COHEFICIENT


uint32_t* Register::getId(){
    return this->id;
}

std::string* Register::getCode(){
    return this->code;
}

std::string* Register::getDescription(){
    return this->description;
}

const char* Register::getStream(){
    std::stringstream ss;
    unsigned char end = 255;
    ss << (char)*this->getId() << *this->getCode() << *this->getDescription() << end ;
    const char* p = ss.str().c_str();
    return p;
}

void Register::setCode(const char* code){
    delete this->code;
    this->code = new std::string(code);
}

void Register::setDescription(const char* description){
    delete this->description;
    this->description = new std::string(description);
}

void Register::setId(int id){
    delete this->id;
    this->id = new uint32_t(id);
}

Register::Register(uint32_t id, const char* code, const char* description){
    this->id = new uint32_t(id);
    this->code = new std::string(code);
    this->description = new std::string(description);
}

Register::Register(char* biteString){

    this->id = new uint32_t((uint32_t)biteString[0]);
    this->code = new std::string(&biteString[1], 3);

    uint32_t i = 4;

    for(; biteString[i] != 0xFF ; i++);

    std::cout << "Break point" << std::endl;
    std::cout << (int)i << std::endl;

    this->description = new std::string(4, i);

    std::cout << this->description << std::endl;
}

Register::Register(Register* _register){
    this->id = new uint32_t(*_register->id);
    this->code = new std::string(*_register->code);
    this->description = new std::string(*_register->description);
}

uint32_t Register::getSize(){
    return (sizeof(*this->id) + sizeof(*this->code) + sizeof(*this->description) + 1);
}

Register::~Register(void){
    delete this->id;
    delete this->code;
    delete this->description;
}
