#include "../DataAccess/File.hpp"
#include "../Common/InnerNode.hpp"
#include "../Common/LeafNode.hpp"
#include "../Common/Node.hpp"
#include "./FractalTree.hpp"
#include "./Common/Register.hpp"
#include "./NodeContainer.hpp"
#include <iostream>
#include <fstream>
#include <string.h>

#define PATH ./test.bin

FractalTree::FractalTree(){
	this->file = new File(PATH, 4096);
}

Register FractalTree::getValue(uint32_t id){
		return this->getValue(id, 1);
}

Register FractalTree::getValue(uint32_t id, uint32_t nodePlace){
	Node* node = this->file.getNode(nodePlace);
	switch (node->getType()) {
		case 0:
			return this->getValue(id, ((InnerNode*)node)->getDirection(id));
		case 1:
			return ((LeafNode*)node)->getRegister(id);
	}
}

bool FractalTree::setValue(Register* _register){
	return this->setValue(id, 1);
}

bool FractalTree::setValue(Register* _register, uint32_t nodePlace){
	Node* node = this->file.getNode(nodePlace);
	switch (node->getType()) {
		case 0:
			return this->setValue(id, ((InnerNode*)node)->getDirection(id));
		case 1:
			((LeafNode*)node)->insertRegister(_register);
			if( !this->file.saveNode(nodePlace, node) ){
			}
			return true;
	}
}

FractalTree::deleteValue(uint32_t id){

}

FractalTree::findValue(uint32_t id){

}
