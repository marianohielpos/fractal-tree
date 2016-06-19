#include "../DataAccess/File.hpp"
#include "../Common/Register.hpp"
#include "../Common/Node.hpp"

#ifndef _FRACTALTREE_H_
#define _FRACTALTREE_H_

class FractalTree
{

public:

	Register getValue(uint32_t id);

	bool setValue(Register* _register);

	bool deleteValue(uint32_t id);

protected:

private:

	FractalTree::findValue(uint32_t id);

	stack<NodeContainer> nodes;
	File* file;

};


#endif // _F_TREE_H_
