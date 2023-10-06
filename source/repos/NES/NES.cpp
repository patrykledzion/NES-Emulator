#include <iostream>
#include "Memory.h"
#include "c6502.h"

int main()
{
   
    Memory* mem = new Memory();
    c6502* cpu = new c6502();
    

    //TESTS
    std::cout << "TESTY:" << std::endl;
    cpu->X = 0x10;
    mem->data[0] = c6502::OP_LDA_AB; 
    mem->data[1] = 0xAB;
    mem->data[2] = 0xCD;
    mem->data[0xCDAB] = 0x69;

    cpu->execute(4, *mem);
    
    return 0;
}

