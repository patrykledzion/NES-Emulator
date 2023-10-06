#pragma once
#include <cstdint>

using Byte = uint8_t;
using Word = uint16_t;

class Memory
{
public:
	static constexpr int MAX_MEM = 1024 * 64;
	Byte data[MAX_MEM]{};

	Memory();
	Byte operator[](Word addr) const
	{
		return data[addr];
	}

	Byte& operator[](Word addr)
	{
		return this->data[addr];
	}
};

