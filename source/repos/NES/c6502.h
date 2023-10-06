#pragma once

#include <iostream>
#include "Memory.h"

struct PS_t {
	int C;
	int Z;
	int I;
	int D;
	int B;
	int V;
	int N;
};

class c6502
{
public:
	//Registers
	Word PC, SP;
	Byte A, X, Y;
	PS_t PS;

	//Instructions Opcodes
	static constexpr Byte OP_LDA_IM		= 0xA9;
	static constexpr Byte OP_LDA_ZP		= 0xA5;
	static constexpr Byte OP_LDA_ZPX	= 0xB5;
	static constexpr Byte OP_LDA_AB		= 0xAD;
	static constexpr Byte OP_LDA_ABX	= 0xBD;
	static constexpr Byte OP_LDA_ABY	= 0xB9;
	static constexpr Byte OP_LDA_INX	= 0xA1;
	static constexpr Byte OP_LDA_INY	= 0xB1;

	//Instructions
	void INS_LDA(Byte val);

	//Other
	Byte ReadByte(int& cycles, Memory& mem);

	//Addressing Modes Getters
	Byte AM_Immediate(int& cycles, Memory& mem);
	Byte AM_ZeroPage(int& cycles, Memory& mem);
	Byte AM_ZeroPageX(int& cycles, Memory& mem);
	Byte AM_Absolute(int& cycles, Memory& mem);
	Byte AM_AbsoluteX(int& cycles, Memory& mem);
	Byte AM_AbsoluteY(int& cycles, Memory& mem);

	
public:
	c6502();
	void execute(int cycles, Memory& mem);

};

