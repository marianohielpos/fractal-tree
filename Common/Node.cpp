/*
*   The responsability of releasing the dinamic memory of the node is given
*   to the one who is the last one that uses the node.
*
*/

#include "Register.hpp"

#include "Node.hpp"
#include <string>
#include <iostream>
#include <sstream>

#define FRACTAL_COHEFICIENT


void Node::setRegister(Register* _register){
    this->_register = new Register(_register);
}

Register* Node::getRegister(uint32_t* id){
    return this->_register;
}

const char* Node::getStream(){
    //TODO
    return this->_register->getStream();
}

uint32_t Node::getSize(){
    return this->_register->getSize();
}

Node::Node(){
}

Node::Node(char* biteStream){
    this->_register = new Register(biteStream);
}

Node::~Node(void){
    delete this->_register;
}
