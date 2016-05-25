/* File description:
*  First fourth blocks: Metadata, bytemap;
*  Other blocks: Data
*  Free space control: Bytemap, representing the percentage of use of each block
*  Each register is finished with a EOF
*/
#include "file.h"
#include "register.h"

#include <iostream>
#include <fstream>

#define DATABASE_NAME "./database.bin" //Need to set as a parameter
#define REGISTER_SIZE 4096 //The max size of the register in bytes

File::getRawRegister(uint registerNumber) {

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

File::getRegister(uint registerNumber) {

    return new Register(this.getRawRegister(registerNumber));

}

File::saveRegister(){

}
