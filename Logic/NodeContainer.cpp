#include "../Common/Node.hpp"

#ifndef _NODECONTAINER_H_
#define _NODECONTAINER_H_

class FractalTree
{

public:

	Node getNode();

	void setNode(Node node,uint32_t place);

	uint32_t getPlace();

protected:

private:

	Node node;
    uint32_t place;

};

#endif
