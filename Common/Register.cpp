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


uint32_t Register::getId(){
    return this->id;
}

const char* Register::getCode(){
    return this->code.c_str();
}

const char* Register::getDescription(){
    return this->description.c_str();
}

const char* Register::getStream(){
    std::stringstream ss;
    const char end = 0xFF;
    ss << this->getId() << this->getCode() << this->getDescription() << end ;
    const char* p = ss.str().c_str();
    return p;
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

Register::Register(char* biteString){

    this->id = (uint32_t)(biteString[3] << 24 | biteString[2] << 16 | biteString[1] << 8 | biteString[0]);
    std::cout << (uint32_t)biteString[0] << std::endl;
    std::cout << (uint32_t)biteString[1] << std::endl;
    std::cout << (uint32_t)biteString[2] << std::endl;
    std::cout << (uint32_t)biteString[3] << std::endl;
    std::cout << (uint32_t)biteString[4] << std::endl;

    std::cout << (uint32_t)biteString[5] << std::endl;

    std::cout << (uint32_t)biteString[6] << std::endl;

    std::cout << (uint32_t)biteString[7] << std::endl;

    std::cout << (uint32_t)biteString[8] << std::endl;

    this->code = std::string(&biteString[1], 3);

    uint32_t i = 4;

    for(; (char)biteString[i] != (char)0xFF ; i++);

    this->description = std::string(4, i);
}

Register::Register(Register* _register){
    this->id = _register->id;
    this->code = std::string(_register->code);
    this->description = std::string(_register->description);
}

uint32_t Register::getSize(){
    return (sizeof(this->id) + sizeof(this->code) + sizeof(this->description) + 1);
}

Register::~Register(void){
}
