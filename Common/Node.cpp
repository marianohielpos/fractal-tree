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

#define FRACTAL_COHEFICIENT 8


void Node::setRegister(Register& _register){
    this->_register = Register(_register);
}

Register Node::getRegister(uint32_t* id){
    return this->_register;
}

bool Node::getStream(char* buffer, uint32_t size){

    return this->_register.getStream(buffer, size);
}

uint32_t Node::getSize(){
    return this->_register.getSize();
}

Node::Node(const char* byteStream)
    : _register(byteStream){}


Node::~Node(void){
}

Node::Node(){
    Register _register;
}
