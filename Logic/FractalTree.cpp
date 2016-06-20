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
	return this->getRegister(id, 1);
}

Register* FractalTree::getRegister(uint32_t id, uint32_t nodePlace){
	Node* node = this->file->getNode(nodePlace);
	switch (node->getType()) {
		case 0:
			return this->getRegister(id, ((InnerNode*)node)->getDirection(id));
		case 1:
			return ((LeafNode*)node)->getRegister(id);
	}
	return NULL;
}

bool FractalTree::setRegister(Register* _register){
	return this->setRegister(_register, 1);
}

bool FractalTree::setRegister(Register* _register, uint32_t nodePlace){
	Node* node = this->file->getNode(nodePlace);
	switch (node->getType()) {
		case 0:
			return this->setRegister(_register, ((InnerNode*)node)->getDirection(_register->getId()	));
		case 1:
			std::cout << "Saving register" << std::endl;
			((LeafNode*)node)->insertRegister(_register);
			if( !this->file->saveNode(node, nodePlace)){
				std::cout << "Warning error" << std::endl;
			}
			return true;
	}

	return false;
}

bool FractalTree::deleteRegister(uint32_t id){
	return true;
}
