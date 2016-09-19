#include"sic.h"
using namespace std;

void SIC::LDA(short addr)
{
	A.opcode = memory[addr];
	short t = memory[addr + 1];
	t = t << 8;
	A.address = t | memory[addr + 2];
}

void SIC::STA(short addr)
{
	memory[addr] = A.opcode;
	memory[addr + 1] = A.address >> 8;
	memory[addr + 2] = A.address & 255;
}


