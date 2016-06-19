#include "./NodeContainer.hpp"


Node NodeContainer::getNode(){
    return this->node;
}

void  NodeContainer::setNode(Node node,uint32_t place){
    this->node = node;
    this->place = place;
}

uint32_t  NodeContainer::getPlace(){
    return this->place;
}
