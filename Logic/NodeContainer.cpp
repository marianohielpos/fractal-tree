#include "./NodeContainer.hpp"


InnerNode* NodeContainer::getNode(){
    return this->node;
}

NodeContainer::NodeContainer(InnerNode* node,uint32_t place){
    this->node = node;
    this->place = place;
}

uint32_t  NodeContainer::getPlace(){
    return this->place;
}
