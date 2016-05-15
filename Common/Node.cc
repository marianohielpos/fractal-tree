/*
*   The responsability of releasing the dinamic memory of the node is given
*   to the one who is the last one that uses the node.
*
*/

#include "node.h"

Node::getId(){
    return id;
}

Node::setId(int foreignId){
    id = foreignId;
}

Node::getCod(){
    return cod;
}

Node::setCod(std::string cod){
    cod.copy(cod,CODE_SIZE);
}

Node::setDescription(std::string foreignDescription){
    description = foreignDescription;
}

Node::getDescription(){
    return description;
}

Node::Node(int* id, char* cod, char* description){
    this.id = id;
    this.cod = cod;
    this.description = description;
}
