#include "../DataAccess/File.hpp"
#include "../Common/Register.hpp"
#include "../Common/Node.hpp"
#include "../Common/LeafNode.hpp"
#include "./NodeContainer.hpp"

#include <stack>

#ifndef _FRACTALTREE_H_
#define _FRACTALTREE_H_

class FractalTree
{
public:

	Register* getRegister(uint32_t id);

	Register* getRegister(uint32_t id, uint32_t nodePlace, uint32_t level);

	bool setRegister(Register* _register);

	bool setRegister(Register* _register, uint32_t nodePlace, uint32_t level);

	bool deleteRegister(uint32_t id);

	FractalTree(const char* path);

protected:

private:

	std::vector<LeafNode> splitNode(LeafNode* node);

	File* file;

};


#endif // _F_TREE_H_
