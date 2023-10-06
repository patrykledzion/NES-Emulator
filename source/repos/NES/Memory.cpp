#include "Memory.h"

Memory::Memory()
{
	for (Byte i : this->data)
	{
		i = 0;
	}
}
