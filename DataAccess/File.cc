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


 /* File description:
 *  First fourth blocks: Metadata, bytemap and (Need to think)
 *  Other blocks: Data
 *  Free space control: Bytemap, representing the percentage of use of each block
 *  Each register is finished with a EOF
 *
 */

#include "file.h"
#include "register.h"

#include <iostream>
#include <fstream>

#define DATABASE_NAME "./database.bin" //Need to set as a parameter
#define REGISTER_SIZE 4096 //The max size of the register in bytes

File::getRegister(uint registerNumber) {

    int blockPosition = registerNumber * REGISTER_SIZE;
    char* memblock;

    myfile.open (DATABASE_NAME, ios::out | ios::in | ios::binary);

    if ( !myfile.is_open() ) {
      //TODO: Handle error
      return;
    }

    memblock = new char [REGISTER_SIZE];
    file.seekg (0, blockPosition);
    file.read (memblock, REGISTER_SIZE);
    file.close();

    myfile.close();

    return new Register(memblock);
}
