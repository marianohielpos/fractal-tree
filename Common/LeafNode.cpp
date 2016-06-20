#include "./Register.hpp"
#include "./LeafNode.hpp"

#include <string>
#include <stdint.h>
#include <vector>
#include <map>
#include <cstring>

LeafNode::LeafNode(){}

uint32_t LeafNode::getType(){
    return 1;
}

uint32_t LeafNode::getMin(){
    return this->registers.lower_bound(0)->first;
}

bool LeafNode::getStream(char* buffer, uint32_t size){
    std::cout << "Serializing node" << std::endl;

    char oneChar = 0x01;

    if( !buffer || this->getSize() > size){
        std::cout << "Warning buffer is not capable" << std::endl;
        return false;
    }

    //Inner node starts with a one
    memcpy(buffer, &oneChar, sizeof(char));

    this->serializeRegisters(buffer + 1);

    return true;

}

uint32_t LeafNode::getSize(){
    //First char indicating type and 4 for the size
    uint32_t size = 5;

    std::map<uint32_t,Register>::iterator iterator = this->registers.begin();

    for (; iterator != this->registers.end(); ++iterator){
        size += iterator->second.getSize();
    }

    return size;
}

LeafNode::LeafNode(const char* byteStream)
    : Node()
    {

	//Avoid the first byte
	this->deSerializeRegisters(byteStream + 1);
}

LeafNode::~LeafNode(){}
