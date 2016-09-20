#include<fstream>
#include<iostream>
#include<iomanip>
#include"interpreter.h"
using namespace std;

Interpreter::Interpreter(string file)
{
	load_to_memory(file);
	show_mem();
	while(PC < data_begin) execute();
	show_mem();
}

void Interpreter::load_to_memory(string file)
{
	ifstream f(file);
	string s;
	int addr, mnemonic;
	f >> s >> hex >> start >> s >> hex >> data_begin >> s >> hex >> end;
	while(f >> hex >> addr >> hex >> mnemonic) {
		memory[addr] = mnemonic >> 16;
		memory[addr + 1] = (mnemonic >> 8) & 255;
		memory[addr + 2] = mnemonic & 255;
	}
	PC = start;
}

void Interpreter::show_mem()
{
	for(int i = start; i < end; i++) {
		cout << setfill('0') << setw(2) << hex << +memory[i];
		if(i % 3 == 2) cout << ' ';
	}
}

void Interpreter::execute()
{
	short operand = memory[PC + 1];
	operand <<= 8;
	operand |= memory[PC + 2];
	po_table[memory[PC]](operand);
	PC.address += 3;
}

void Interpreter::fetch()
{
}
