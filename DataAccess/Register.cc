#include "Register.h"
#include "Node.h"
#include <iostream>
#include <string>

#define END_OF_REGISTER 255 //Forbiden char character

Register::register(char* stream){

    std::vector<Node> nodes = null;

    std::string node = '';

    for(uint i = 0; stream[i] != END_OF_REGISTER ; i++){

        node.append(stream[i])

        if( stream[i] == '\0' ){
            int id = node[0] + node[1] + node[3];

            std::string code;
            node.copy(code, 3, 4); //Copy the three letters of the codes

            std::string message;
            node.copy(message, node.length() - 7, 7); //Copy the description

            nodes.push_back(new Node(id, code, message));
            node = '';
        }

    }

    return nodes;
}

Register::register(std::vector<Node> nodes){

}
