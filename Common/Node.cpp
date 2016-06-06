/*
*   The responsability of releasing the dinamic memory of the node is given
*   to the one who is the last one that uses the node.
*
*/

#include "Node.hpp"
#include <string>
#include <iostream>
#include <sstream>

#define FRACTAL_COHEFICIENT


size_t* Node::getId(){
    return this->id;
}

std::string* Node::getCode(){
    return this->code;
}

std::string* Node::getDescription(){
    return this->description;
}

const char* Node::getStream(){
    std::stringstream ss;
    unsigned char end = 255;
    ss << *this->getDescription() << *this->getCode() <<  (char)*this->getId() << end ;
    const char* p = ss.str().c_str();
    return p;
}

void Node::setCode(const char* code){
    delete this->code;
    this->code = new std::string(code);
}

void Node::setDescription(const char* description){
    delete this->description;
    this->description = new std::string(description);
}

void Node::setId(int id){
    delete this->id;
    this->id = new size_t(id);
}

Node::Node(size_t id, const char* code, const char* description){
    this->id = new size_t(id);
    this->code = new std::string(code);
    this->description = new std::string(description);
}

Node::Node(char* biteString){
    //TODO
}

size_t Node::getSize(){
    return sizeof(this->id) + sizeof(this->code) + sizeof(this->description) + 1;
}

Node::~Node(void){
    delete this->id;
    delete this->code;
    delete this->description;
}
