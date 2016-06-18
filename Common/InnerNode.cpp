#include "./InnerNode.hpp"

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

uint32_t InnerNode::getReference(uint32_t nodeId){
    return this->references[nodeId];
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

    if( !buffer || this->getSize() > size){
        std::cout << "Warning buffer is not capable" << std::endl;
        return false;
    }

    //Inner node starts with a cero
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

    memcpy(buffer + offset, this->getBuffer(), strlen(this->getBuffer()));

    return true;

}

const char* InnerNode::getBuffer(){
    return this->buffer.c_str();
}

void InnerNode::insertInBuffer(const char* _register){
    this->buffer.append(_register);
    this->buffer.append('\0');
}

uint32_t InnerNode::getSize(){
    uint32_t size = 0;

    //Type of node
    size += 1;
    //Space occupied for the whole
    size += 4;
    //References plus null character
    size += this->references.size()*8 + 1;
    //Buffers plus null character
    size += strlen(this->getBuffer()) + 1;

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
    //Avoid the first byte
    uint32_t offset = 1;
    uint32_t numberOfReferences = 0;

    memcpy(&numberOfReferences, byteStream + offset, sizeof(uint32_t));

    offset += sizeof(uint32_t);

    uint32_t i = offset;

    uint32_t key;
    uint32_t value;

    for(uint32_t j = 0; j < numberOfReferences; j++ ){
        memcpy(&key, byteStream + offset, sizeof(uint32_t));
        memcpy(&value, byteStream + offset + 4, sizeof(uint32_t));

        offset += 8;
        this->references[key] = value;
    }

    i += 1;
    offset = i;

    for(; (char)byteStream[i] != '\0' ; ++i);

    this->buffer = std::string(&byteStream[offset], i);

}
