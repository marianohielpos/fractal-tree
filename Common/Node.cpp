/*
*   The responsability of releasing the dinamic memory of the node is given
*   to the one who is the last one that uses the node.
*
*/

#include "Node.hpp"
#include <string>
#include <iostream>
#include <sstream>


int* Node::getId(){
    return this->id;
}

std::string* Node::getCode(){
    return this->code;
}

std::string* Node::getDescription(){
    return this->description;
}

std::string* Node::getFields(){
    std::stringstream ss;
    ss << *this->getDescription() << *this->getCode() <<  (char)*this->getId();
    return new std::string(ss.str());
}

void Node::setCode(const char* code){
    delete this->code;
    this->code = new std::string(code);
}

void Node::setDescription(const char* description){
    delete this->description;
    this->description = new std::string(description);
}

void Node::setId(int* id){
    delete this->id;
    this->id = new int(*id);
}

Node::Node(int* id, const char* code, const char* description){
    this->id = new int(*id);
    this->code = new std::string(code);
    this->description = new std::string(description);
}

Node::~Node(void){
    delete this->id;
    delete this->code;
    delete this->description;
    delete this;
}
