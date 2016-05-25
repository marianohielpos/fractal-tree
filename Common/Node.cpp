/*
*   The responsability of releasing the dinamic memory of the node is given
*   to the one who is the last one that uses the node.
*
*/

#include "Node.hpp"
#include <string>
#include <iostream>

int* Node::getId(){
    return this->id;
}

std::string Node::getCode(){
    return this->cod;
}

std::string Node::getDescription(){
    return this->description;
}

void Node::setCode(std::string cod){
    this->cod = cod;
}

void Node::setDescription(std::string description){
    this->description = description;
}

void Node::setId(int* id){
    this->id = id;
}

Node::Node(int* id, std::string cod, std::string description){
    this->id = id;
    this->cod = cod;
    this->description = description;
}
