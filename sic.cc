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

bool SIC::is_opcode(string s)
{
	return op_table.find(s) != op_table.end();
}

Register& Register::operator=(int n)
{
	address = n & 65535;
	n <<= 8;
	n >>= 24;
	opcode = n;
	return *this;
}

Register::operator int()
{
	int tmp = opcode;
	tmp <<= 16;
	tmp |= address;
	return tmp;
}

int SIC::fetch(short addr) const
{
	int r = memory[addr];
	r <<= 16;
	int k = memory[addr + 1];
	k <<= 8;
	r |= k;
	r |= memory[addr + 2];
	return r;
}

void SIC::LDX(short operand) {}
void SIC::STX(short operand) {}
void SIC::ADD(short operand) 
{
	int k = fetch(operand);
	int a = A;
	A = a + k;
}
void SIC::SUB(short operand) {}
void SIC::MUL(short operand) {}
void SIC::DIV(short operand) {}
void SIC::COMP(short operand) {}
void SIC::JEQ(short operand) {}
void SIC::JGT(short operand) {}
void SIC::JLT(short operand) {}
void SIC::JSUB(short operand) {}
void SIC::RSUB(short operand) {}
void SIC::RD(short operand) {}
void SIC::WD(short operand) {}
void SIC::TD(short operand) {}



