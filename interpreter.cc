//인터프리터 구현부.
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
	char c[5];
	int addr, mnemonic;
	f >> s >> hex >> start >> s >> hex >> data_begin >> s >> hex >> end;
	addr = start;
	while(f >> s >> s) {
		for(int i=0; i<s.size(); i+=2) {
			string n;
			n += s[i];
			n += s[i+1];
			memory[addr++] = stoi(n, nullptr, 16);
		}
	}
	PC = start;
}

void Interpreter::show_mem()
{
	for(int i = data_begin, j = 0; i < end; i++, j++) {
		cout << setfill('0') << setw(2) << hex << +memory[i];
		if(j % 3 == 2) cout << ' ';
	}
	cout << endl;
}

void Interpreter::execute()
{
	short operand = memory[PC + 1];
	operand <<= 8;
	operand |= memory[PC + 2];
	po_table[memory[PC]](operand);
	PC.address += 3;
}
