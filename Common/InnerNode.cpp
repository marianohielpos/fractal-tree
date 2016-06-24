#include "./InnerNode.hpp"
#include "./Register.hpp"

#include <string>
#include <stdint.h>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>
#include <cstring>


void InnerNode::insertReference(uint32_t nodeId, uint32_t offset){
    this->references[nodeId] = offset;
}

std::map <uint32_t,uint32_t>* InnerNode::getReferences(){
    return &this->references;
}

uint32_t InnerNode::getNumberOfReferences(){
    return this->references.size();
}

uint32_t InnerNode::getDirection(uint32_t nodeId){
    std::map<uint32_t, uint32_t>::const_iterator it = this->references.lower_bound(nodeId);

    if( it == this->references.end()){
        it--;
    }

    return it->second;
}

void InnerNode::modifyDirection(uint32_t nodeId, uint32_t value){
    std::map<uint32_t, uint32_t>::iterator it = this->references.lower_bound(nodeId);

    if( it == this->references.end()){
        it--;
    }

    it->second = value;
}


uint32_t InnerNode::getType(){
    return 0;
}

void InnerNode::deleteReference(uint32_t nodeId){
    this->references.erase(nodeId);
}

bool InnerNode::getStream(char* buffer, uint32_t size){

    std::cout << "Serializing node" << std::endl;

    uint32_t offset = 0;
    char nullChar = '\0';

    std::map<uint32_t,uint32_t>::iterator iterator = this->references.begin();

    //Inner node starts with a zero
    memcpy(buffer, &nullChar, sizeof(char));

    offset += 1;

    uint32_t numberOfReferences = this->references.size();

    //Number of references
    memcpy(buffer + offset, &numberOfReferences, sizeof(numberOfReferences));

    offset += sizeof(numberOfReferences);

    for (; iterator != this->references.end(); ++iterator){

        memcpy(buffer + offset, &iterator->first, sizeof(iterator->first));

        offset += sizeof(iterator->first);

        memcpy(buffer + offset, &iterator->second, sizeof(iterator->second));

        offset += sizeof(iterator->second);

    }

    memcpy(buffer + offset, &nullChar, sizeof(char));
    //Plus null character
    offset += 1;

    //this->serializeRegisters(buffer + offset);

    return true;

}

uint32_t InnerNode::getSize(){
    uint32_t size = 0;

    //Type of node
    size += 1;
    //Space occupied for the whole
    size += 4;
    //References plus null character
    size += this->references.size()*8 + 1;
    //Buffers
    std::map<uint32_t,Register>::iterator iterator = this->registers.begin();

    for (; iterator != this->registers.end(); ++iterator){
        size += iterator->second.getSize();
    }

    return size;

}

InnerNode::InnerNode()
    : Node(){
    std::map <uint32_t,uint32_t> references;
    std::string buffer;
}

InnerNode::~InnerNode(){};

InnerNode::InnerNode(const char* byteStream)
    : Node()
    {
    std::cout << "Avoid first char" << std::endl;
    //Avoid the first byte
    uint32_t offset = 1;
    uint32_t numberOfReferences = 0;

    memcpy(&numberOfReferences, byteStream + offset, sizeof(uint32_t));

    std::cout << "Number of references " << numberOfReferences << std::endl;

    offset += sizeof(uint32_t);

    uint32_t key;
    uint32_t value;

    for(uint32_t j = 0; j < numberOfReferences; j++ ){
        memcpy(&key, byteStream + offset, sizeof(uint32_t));
        memcpy(&value, byteStream + offset + 4, sizeof(uint32_t));

        std::cout << "Key: " << key << std::endl;
        std::cout << "Value: " << value << std::endl;

        offset += 8;
        this->references[key] = value;
    }

    //this->deSerializeRegisters(byteStream + offset);
}
