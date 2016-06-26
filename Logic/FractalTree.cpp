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
#include <math.h>

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
	std::cout << "check if register is in buffer" << std::endl;
	if( node->exists(id) ){
		std::cout << "register found in buffer" << std::endl;
		return new Register(*(node->getRegister(id)));
	}
	switch (node->getType()) {
		case 0:
			std::cout << ((InnerNode*)node.get())->getDirection(id) << std::endl;
			std::cout << id << std::endl;
			return this->getRegister(id, ((InnerNode*)node.get())->getDirection(id), level++);
		case 1:
			return new Register(*((LeafNode*)node.get())->getRegister(id));
	}
	return NULL;
}

bool FractalTree::deleteRegister(uint32_t id){
	return this->deleteRegister(id, 1, 1);
}

bool FractalTree::deleteRegister(uint32_t id, uint32_t nodePlace, uint32_t level){
	std::unique_ptr<Node> node(this->file->getNode(nodePlace));
	switch (node->getType()) {
		case 0:
			return this->deleteRegister(id, ((InnerNode*)node.get())->getDirection(id), level++);
		case 1:
			std::cout << "Deleting register" << std::endl;
			if(((LeafNode*)node.get())->removeRegister(id)){
				this->file->saveNode(node.get(), nodePlace);
				return true;
			}
			return false;

	}
	return false;
}


bool FractalTree::setRegister(Register* _register){
	return this->setRegister(_register, 1, 1, NULL);
}

bool FractalTree::setRegister(Register* _register, uint32_t nodePlace, uint32_t level, NodeContainer* upperNode){

	std::unique_ptr<Node> node(this->file->getNode(nodePlace));
	node->insertRegister(_register);

	switch (node->getType()) {
		case 0:
			if( !this->file->saveNode(node.get(), nodePlace)){
				NodeContainer nodeContainer = NodeContainer((InnerNode*)node.get(), nodePlace);
				std::map<uint32_t,Register>::iterator iter = node->getRegisters()->begin();

				for (; iter != node->getRegisters()->end(); iter++){
					this->setRegister(&iter->second, ((InnerNode*)node.get())->getDirection(iter->second.getId()), level + 1, &nodeContainer);
				}

				node->removeRegisters();

				this->file->saveNode(node.get(), nodePlace);

				return true;

			} else {
				return true;
			}
		case 1:
			std::cout << "Saving register" << std::endl;
			if( !this->file->saveNode(node.get(), nodePlace)){
				this->split(_register, node.get(), upperNode, nodePlace, level);
			}
			return true;
	}

	return true;
}

bool FractalTree::split(Register* _register, Node* node, NodeContainer* nodeContainer, uint32_t nodePlace, uint32_t level){
	std::vector<LeafNode> v = this->splitNode((LeafNode*)node);

	uint32_t placeOne = this->file->saveNode(&v[0]);
	uint32_t placeTwo =this->file->saveNode(&v[1]);

	if( (placeOne == 0) | (placeOne == 0)){
		std::cerr << "Warning, couldn't save node" << std::endl;
	}


	if( nodeContainer == NULL ){
		this->file->deleteNode(nodePlace);
		InnerNode newInnerNode = InnerNode();
		newInnerNode.insertReference(v[0].getMin(), placeOne);
		newInnerNode.insertReference(v[1].getMin(), placeTwo);
		this->file->saveNode(&newInnerNode);
		return true;
	}

	InnerNode* innerNode = nodeContainer->getNode();

	std::cout << "\t\tNumber of refenrences " << innerNode->getNumberOfReferences() << std::endl;
	std::cout << "\t\tNode level " << level << std::endl;

	if( innerNode->getNumberOfReferences() == (pow(2, level))){
		InnerNode newInnerNode = InnerNode();
		newInnerNode.insertReference(v[0].getMin(), placeOne);
		newInnerNode.insertReference(v[1].getMin(), placeTwo);
		innerNode->modifyDirection(_register->getId(), this->file->saveNode(&newInnerNode));
	}
	else{
		innerNode->modifyDirection(_register->getId(), placeOne);
		innerNode->insertReference(v[1].getMin(), placeTwo);
	}

	std::cout << "Saving node in " << nodeContainer->getPlace() << std::endl;
	this->file->saveNode(innerNode, nodeContainer->getPlace());

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


void FractalTree::showAll(){
	return this->showAll(1);
}


void FractalTree::showAll(uint32_t nodePlace){
	std::unique_ptr<Node> node(this->file->getNode(nodePlace));

	switch (node->getType()) {
		case 0:
			{
				std::cout << "Enter in case 0" << std::endl;
				std::map<uint32_t,uint32_t>::const_iterator iter = ((InnerNode*)node.get())->getReferences()->begin();

		    	for (; iter != ((InnerNode*)node.get())->getReferences()->end(); iter++){
						std::cout << "tree reference: " << iter->first << "-" << iter->second << std::endl;
						this->showAll(iter->second);
				}
				break;
			}
		case 1:
			std::map<uint32_t,Register>::iterator iterator = node->getRegisters()->begin();

			for (; iterator != node->getRegisters()->end(); ++iterator){
				std::cout << "ID: " << iterator->second.getId() << std::endl;
				std::cout << "description: " << iterator->second.getDescription() << std::endl;
				std::cout << "Code: " << iterator->second.getCode() << std::endl;
			}
			break;
	}
}
