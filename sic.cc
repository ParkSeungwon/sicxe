//SIC/XE 구현부
#include<iostream>
#include"sic.h"
using namespace std;

void SIC::LDA(short addr) { A = fetch(addr); }
void SIC::LDL(short addr) { L = fetch(addr); }
void SIC::LDX(short addr) { X = fetch(addr); }
void SIC::STX(short addr) 
{
	memory[addr] = X.opcode;
	memory[addr + 1] = X.address >> 8;
	memory[addr + 2] = X.address & 255;
}
void SIC::STA(short addr)
{
	memory[addr] = A.opcode;
	memory[addr + 1] = A.address >> 8;
	memory[addr + 2] = A.address & 255;
}
void SIC::STL(short addr)
{
	memory[addr] = L.opcode;
	memory[addr + 1] = L.address >> 8;
	memory[addr + 2] = L.address & 255;
}

bool SIC::is_opcode(string s)
{
	return op_table.find(s) != op_table.end();
}

void SIC::TIX(short addr) {
	X = X + 1;
	int a = A;
	A = X;
	COMP(addr);
	A = a;
}
Register& Register::operator=(int n)
{
	address = n & 0xffff;
	opcode = (n & 0xff0000) >> 16;
	return *this;
}

Register::operator int()
{
	int r = opcode;
	r <<= 16;
	r |= address;
	return r;
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

void SIC::ADD(short addr) { A = A + fetch(addr); } 
void SIC::SUB(short addr) { A = A - fetch(addr); }
void SIC::LDCH(short addr) { A = memory[addr]; }
void SIC::STCH(short addr) { memory[addr] = A.address & 255; }
void SIC::MUL(short addr) { A = A * fetch(addr); }
void SIC::DIV(short addr) { A = A / fetch(addr); }
void SIC::COMP(short addr) 
{
	int n = fetch(addr);
	int a = A;
	if(a == n) SW.opcode = 0;
	else if(a < n) SW.opcode = 1;
	else SW.opcode = 2;
}
void SIC::JEQ(short addr) { if(!SW.opcode) PC = addr - 3; }
void SIC::JGT(short addr) { if(SW.opcode == 2) PC = addr - 3; }
void SIC::J(short addr) { PC = addr - 3; }
void SIC::JLT(short addr) { if(SW.opcode == 1) PC = addr - 3; }
void SIC::JSUB(short addr) {
	L = PC;
	PC = addr - 3;
}

void SIC::RSUB(short addr) { PC = L; }
void SIC::RD(short addr) {
	char c;
	cin >> c;	
	A = (int)c;
}
void SIC::WD(short addr) {
	cout << (char)(A.address & 0xff);
}
void SIC::TD(short addr) {}


