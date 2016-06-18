uint32_t InnerNode::getType(){
    return 1;
}


bool insertOffset(uint32_t offset);


Register Node::getRegister(uint32_t* id){
    return this->registers;
}

bool Node::getStream(char* buffer, uint32_t size){

    return this->registers.getStream(buffer, size);
}

uint32_t Node::getSize(){
    return this->registers.getSize();
}

bool Node::insertRegister(uint32_t place, Register& _register){
    if( place > this->fractalCoeficient ){
        return false;
    }
    this->registers[place] = Register(_register);
    return true;
}

bool Node::insertRegister(Register& _register){
    if( this->registers.size() == this->fractalCoeficient ){
        return false;
    }
    this->registers.push Register(_register);
    return true;
}
s
