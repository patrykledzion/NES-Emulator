#include "c6502.h"

c6502::c6502()
{
	this->PC = 0;
	this->SP = 0;
	this->A = this->X = this->Y = 0;
	this->PS = { 0,0,0,0,0,0,0 };
}

void c6502::execute(int cycles, Memory& mem)
{
	while (cycles > 0)
	{
		Byte ins = this->ReadByte(cycles, mem);
		std::cout << "INS "<<std::hex << (int)ins << std::endl;
		switch (ins)
		{
		case OP_LDA_IM: INS_LDA(AM_Immediate(cycles, mem));		break;
		case OP_LDA_ZP: INS_LDA(AM_ZeroPage(cycles, mem));		break;
		case OP_LDA_ZPX: INS_LDA(AM_ZeroPageX(cycles, mem));	break;
		case OP_LDA_AB: INS_LDA(AM_Absolute(cycles, mem));		break;
		case OP_LDA_ABX: INS_LDA(AM_AbsoluteX(cycles, mem));	break;
		case OP_LDA_ABY: INS_LDA(AM_AbsoluteY(cycles, mem));	break;
		}
	}
}


//Instructions
void c6502::INS_LDA(Byte val)
{
	this->A = val;
	this->PS.Z = (this->A == 0);
	this->PS.N = ((this->A & (1<<7))>>7==1);
}

//Other
Byte c6502::ReadByte(int& cycles, Memory& mem)
{
	cycles--;
	return mem[this->PC++];
}

//Addressing Modes Getter
Byte c6502::AM_Immediate(int& cycles, Memory& mem)
{
	cycles--;
	return mem[this->PC++];
}

Byte c6502::AM_ZeroPage(int& cycles, Memory& mem)
{
	cycles -= 2;
	Byte addr = mem[this->PC++];
	return mem[addr];
}

Byte c6502::AM_ZeroPageX(int& cycles, Memory& mem)
{
	cycles -= 3;
	Byte addr = mem[this->PC++];
	return mem[addr + this->X];
}

Byte c6502::AM_Absolute(int& cycles, Memory& mem)
{
	cycles -= 3;
	Word addr = mem[this->PC++];
	addr |= (mem[this->PC++] << 8);
	std::cout << std::hex << "ADDR "<<(int)addr << std::endl;
	return mem[addr];
}

Byte c6502::AM_AbsoluteX(int& cycles, Memory& mem)
{
	cycles -= 3;
	Byte addr = mem[this->PC++];
	addr |= mem[this->PC++] << 8;
	if (addr <=0xFF && addr + this->X > 0xFF)cycles--;
	return mem[addr + this->X];
}

Byte c6502::AM_AbsoluteY(int& cycles, Memory& mem)
{
	cycles -= 3;
	Byte addr = mem[this->PC++];
	addr |= mem[this->PC++] << 8;
	if (addr <= 0xFF && addr + this->Y > 0xFF)cycles--;
	return mem[addr + this->Y];
}



