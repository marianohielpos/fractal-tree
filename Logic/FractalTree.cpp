#include "../DataAccess/File.hpp"
#include "../Common/InnerNode.hpp"
#include "../Common/LeafNode.hpp"
#include "../Common/Node.hpp"
#include "./FractalTree.hpp"
#include "../Common/Register.hpp"
#include "./NodeContainer.hpp"
#include <iostream>
#include <fstream>
#include <string.h>
#include <memory>


#define PATH ./test.bin
#define BLOCK_SIZE 4096

FractalTree::FractalTree(const char* pathToFile){
	this->file = new File(pathToFile, BLOCK_SIZE);
}

FractalTree::~FractalTree(){
	delete this->file;
}

Register* FractalTree::getRegister(uint32_t id){
	return this->getRegister(id, 1, 1);
}

Register* FractalTree::getRegister(uint32_t id, uint32_t nodePlace, uint32_t level){
	std::cout << "nodePlace " << nodePlace << std::endl;
	std::unique_ptr<Node> node(this->file->getNode(nodePlace));
	switch (node->getType()) {
		case 0:
		std::cout << ((InnerNode*)node.get())->getDirection(id) << std::endl;
			return this->getRegister(id, ((InnerNode*)node.get())->getDirection(id), level++);
		case 1:
			return ((LeafNode*)node.get())->getRegister(id);
	}
	return NULL;
}

bool FractalTree::deleteRegister(uint32_t id){
	Node* node = this->file->getNode(1);
	switch (node->getType()) {
		case 0:
			//TODO return this->getRegister(id, ((InnerNode*)node)->getDirection(id), 1, 1);
		case 1:
			std::cout << "Deleting register" << std::endl;
			((LeafNode*)node)->removeRegister(id);
			if( !this->file->saveNode(node, 1)){
				std::cout << "Warning error" << std::endl;
			}
			return true;
	}
	return false;
}


bool FractalTree::setRegister(Register* _register){
	return this->setRegister(_register, 1, 1);
}

bool FractalTree::setRegister(Register* _register, uint32_t nodePlace, uint32_t level){

	std::stack<NodeContainer> nodes;
	std::stack<Node*> nodesToFree;
	Node* node = NULL;

	while (true) {
		node = this->file->getNode(nodePlace);
		nodesToFree.push(node);
		switch (node->getType()) {
			case 0:
				nodes.push(NodeContainer((InnerNode*)node, nodePlace));
				nodePlace = ((InnerNode*)node)->getDirection(_register->getId());
				std::cout << "Direction: " << nodePlace << std::endl;
				break;
			case 1:
				std::cout << "Saving register" << std::endl;
				((LeafNode*)node)->insertRegister(_register);
				if( !this->file->saveNode(node, nodePlace)){
					this->split(_register, node, &nodes, nodePlace, level);
				}
				this->free(&nodesToFree);
				return true;
		}

		level++;

	}

	return true;
}

bool FractalTree::free(std::stack<Node*>* nodesToFree){
	while ( !nodesToFree->empty()) {
		delete nodesToFree->top();
		nodesToFree->pop();
	}
	return true;
}

bool FractalTree::split(Register* _register, Node* node, std::stack<NodeContainer> *nodes, uint32_t nodePlace, uint32_t level){
	std::vector<LeafNode> v = this->splitNode((LeafNode*)node);

	uint32_t placeOne = this->file->saveNode(&v[0]);
	uint32_t placeTwo =this->file->saveNode(&v[1]);

	if( (placeOne == 0) | (placeOne == 0)){
		std::cerr << "Warning, couldn't save node" << std::endl;
	}


	if( nodes->empty() ){
		this->file->deleteNode(nodePlace);
		InnerNode newInnerNode = InnerNode();
		newInnerNode.insertReference(v[0].getMin(), placeOne);
		newInnerNode.insertReference(v[1].getMin(), placeTwo);
		this->file->saveNode(&newInnerNode);
		return true;
	}

	NodeContainer nodeContainer = nodes->top();
	nodes->pop();

	InnerNode* innerNode = nodeContainer.getNode();

	if( innerNode->getNumberOfReferences() == (2 ^ level)){
		InnerNode newInnerNode = InnerNode();
		newInnerNode.insertReference(v[0].getMin(), placeOne);
		newInnerNode.insertReference(v[1].getMin(), placeTwo);
		innerNode->modifyDirection(_register->getId(), this->file->saveNode(&newInnerNode));
	}
	else{
		innerNode->modifyDirection(_register->getId(), placeOne);
		innerNode->insertReference(v[1].getMin(), placeTwo);
	}

	std::cout << "Saving node in " << nodeContainer.getPlace() << std::endl;
	this->file->saveNode(innerNode, nodeContainer.getPlace());

	return true;

}

std::vector<LeafNode> FractalTree::splitNode(LeafNode* node){
	std::vector<LeafNode> v;

	std::map<uint32_t,Register>* registers = node->getRegisters();

	uint32_t size = registers->size();

	std::map<uint32_t,Register>::iterator iterator = registers->begin();

	LeafNode leafNodeOne = LeafNode();
	LeafNode leafNodeTwo = LeafNode();

	uint32_t i = 0;

	for(; i < size /2; i++){
		leafNodeOne.insertRegister(&iterator->second);
		iterator++;
	}

	for(; i < size; i++){
		leafNodeTwo.insertRegister(&iterator->second);
		iterator++;
	}

	v.push_back(leafNodeOne);
	v.push_back(leafNodeTwo);

	return v;
}
