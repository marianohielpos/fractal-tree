/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*-  */
/*
 * node.h
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

#include <std>
#define CODE_SIZE 3



#ifndef _NODE_H_
#define _NODE_H_



class Node
{
public:

    int getId();

    void setId(int foreignId);

    char* getCod();

    void setCod(std::string cod);

    char* setDescription(std::string foreignDescription);

    char* getDescription();

protected:

    int id;
    std::string cod[CODE_SIZE + 1];  //+1 for the end character
    std::string description;

private:


};

#endif // _NODE_H_
