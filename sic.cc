//SIC/XE 구현부
#include"sic.h"
using namespace std;

void SIC::LDA(short addr)
{
	A = fetch(addr);
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

void SIC::LDX(short addr) 
{
	X = fetch(addr);
}
void SIC::STX(short addr) 
{
	memory[addr] = X.opcode;
	memory[addr + 1] = X.address >> 8;
	memory[addr + 2] = X.address & 255;
}
void SIC::ADD(short addr) 
{
	int n = fetch(addr);
	int a = A;
	A = a + n;
}
void SIC::SUB(short addr)
{
	int n = fetch(addr);
	int a = A;
	A = a - n;
}

void SIC::LDCH(short addr)
{
	A = memory[addr];
}

void SIC::STCH(short addr)
{
	memory[addr] = A.address & 255;
}

void SIC::MUL(short addr) 
{
	int n = fetch(addr);
	int a = A;
	A = a * n;
}
void SIC::DIV(short addr) 
{
	int n = fetch(addr);
	int a = A;
	A = a / n;
}
void SIC::COMP(short addr) {}
void SIC::JEQ(short addr) {}
void SIC::JGT(short addr) {}
void SIC::JLT(short addr) {}
void SIC::JSUB(short addr) {}
void SIC::RSUB(short addr) {}
void SIC::RD(short addr) {}
void SIC::WD(short addr) {}
void SIC::TD(short addr) {}



