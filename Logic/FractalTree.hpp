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

	void showAll();

	bool setRegister(Register* _register);

	bool deleteRegister(uint32_t id);

	FractalTree(const char* path);

	~FractalTree();

protected:

private:

	bool deleteRegister(uint32_t id, uint32_t nodePlace, uint32_t level);

	void showAll(uint32_t nodePlace);

	bool setRegister(Register* _register, uint32_t nodePlace, uint32_t level, NodeContainer* upperNode);

	Register* getRegister(uint32_t id, uint32_t nodePlace, uint32_t level);

	std::vector<LeafNode> splitNode(LeafNode* node);

	bool split(Register* _register, Node* node, NodeContainer* nodeContainer, uint32_t nodePlace, uint32_t level);
	File* file;

	bool free(std::stack<Node*>* nodesToFree);

};


#endif // _F_TREE_H_
