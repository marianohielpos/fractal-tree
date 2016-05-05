/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * file.cc
 * Copyright (C) 2016 Rorri Datos <rncorral@yahoo.com.ar>
 *
 * fractal-tree.git is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * fractal-tree.git is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Register.h"
#include "Node.h"
#include <iostream>
#include <string>

#define END_OF_REGISTER 255


Register::register(char* stream){

    std::vector<Node> nodes = null;

    std::string node = '';

    for(uint i = 0; stream[i] != END_OF_REGISTER ; i++){

        node.append(stream[i])

        if( stream[i] == '\0' ){
            nodes.push_back(new Node(node));
            node = '';
        }

    }

    return nodes;
}

Register::register(std::vector<Node> nodes){
    
}
