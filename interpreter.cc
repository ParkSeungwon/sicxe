//인터프리터 구현부.
#include<fstream>
#include<iostream>
#include<sstream>
#include<iomanip>
#include"interpreter.h"
using namespace std;

Interpreter::Interpreter(string file)
{
	load_to_memory(file);
	while(PC < data_begin) execute();
}

void Interpreter::load_to_memory(string file)
{
	ifstream f(file);
	string s;
	int addr;
	f >> s >> hex >> start >> s >> hex >> data_begin >> s >> hex >> end;
	addr = start;
	stringstream ss;
	while(f >> s >> s) ss << s;
	while(ss >> setw(2) >> s) memory[addr++] = stoi(s, nullptr, 16);
	PC = start;
}

void Interpreter::show_mem()
{
	cout << "A : " << hex << A << ", X : " << hex << X << ", PC : " << PC << endl;
	for(int i = data_begin, j = 0; i < end; i++, j++) {
		cout << setfill('0') << setw(2) << hex << +memory[i];
		if(j % 3 == 2) cout << ' ';
	}
	cout << endl;
}

void Interpreter::execute()
{
	show_mem();
	short operand = memory[PC + 1];
	operand <<= 8;
	operand |= memory[PC + 2];
	po_table[memory[PC]](operand);
	PC.address += 3;
}
