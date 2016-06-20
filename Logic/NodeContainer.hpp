#include "../Common/InnerNode.hpp"

#ifndef _NODECONTAINER_H_
#define _NODECONTAINER_H_

class NodeContainer
{

public:

	InnerNode* getNode();

	NodeContainer(InnerNode* node,uint32_t place);

	uint32_t getPlace();

protected:

private:

	InnerNode* node;
    uint32_t place;

};

#endif
