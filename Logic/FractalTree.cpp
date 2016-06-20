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

#define PATH ./test.bin
#define BLOCK_SIZE 4096

FractalTree::FractalTree(const char* pathToFile){
	this->file = new File(pathToFile, BLOCK_SIZE);
}

Register* FractalTree::getRegister(uint32_t id){
	return this->getRegister(id, 1, 1);
}

Register* FractalTree::getRegister(uint32_t id, uint32_t nodePlace, uint32_t level){
	Node* node = this->file->getNode(nodePlace);
	switch (node->getType()) {
		case 0:
			return this->getRegister(id, ((InnerNode*)node)->getDirection(id), level++);
		case 1:
			return ((LeafNode*)node)->getRegister(id);
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
	Node* node = NULL;

	while (true) {
		bool savedFileUnsuccessful = false;
		node = this->file->getNode(nodePlace);
		switch (node->getType()) {
			case 0:
				nodes.push(NodeContainer((InnerNode*)node, nodePlace));
				nodePlace = ((InnerNode*)node)->getDirection(_register->getId());
				break;
			case 1:
				std::cout << "Saving register" << std::endl;
				((LeafNode*)node)->insertRegister(_register);
				if( !this->file->saveNode(node, nodePlace)){
					savedFileUnsuccessful = true;
					break;
				}
				return true;
		}

		if( savedFileUnsuccessful ){
			break;
		}

		level++;

	}

	std::vector<LeafNode> v = this->splitNode((LeafNode*)node);

	uint32_t placeOne = this->file->saveNode(&v[0]);
	uint32_t placeTwo =this->file->saveNode(&v[1]);

	if( (placeOne == 0) | (placeOne == 0)){
		std::cerr << "Warning, couldn't save node" << std::endl;
	}

	InnerNode newInnerNode = InnerNode();

	if( nodes.empty() ){
		this->file->deleteNode(nodePlace);
		nodes.push(NodeContainer(&newInnerNode, nodePlace));
	}

	NodeContainer nodeContainer = nodes.top();
	nodes.pop();

	InnerNode* innerNode = nodeContainer.getNode();

	if( innerNode->getNumberOfReferences() == (2 ^ level)){
		newInnerNode.insertReference(v[0].getMin(), placeOne);
		newInnerNode.insertReference(v[1].getMin(), placeTwo);
		innerNode->modifyDirection(_register->getId(), this->file->saveNode(&newInnerNode));
	}
	else{
		innerNode->modifyDirection(_register->getId(), placeOne);
		innerNode->insertReference(v[1].getMin(), placeTwo);
	}

	this->file->saveNode(&newInnerNode, nodeContainer.getPlace());

	return false;
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
