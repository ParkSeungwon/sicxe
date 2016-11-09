//인터프리터 구현부.
#include<fstream>
#include<iostream>
#include<sstream>
#include<iomanip>
#include"interpreter.h"
using namespace std;

Interpreter::Interpreter(string file, bool debug)
{
	load_to_memory(file);
	while(PC != data_begin) execute(debug);
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
	cout << "A : " << setfill('0') << setw(6) << hex << A;
	cout << ", X : " << setfill('0') << setw(6) << hex << X;
	cout << ", L : " << setfill('0') << setw(6) << hex << L;
	cout << ", PC : " << setfill('0') << setw(6) << hex << PC;
	cout << ", SW : " << setfill('0') << setw(6) << hex << SW << endl;
	for(int i = data_begin, j = 0; i < end; i++, j++) {
		cout << setfill('0') << setw(2) << hex << +memory[i];
		if(j % 3 == 2) cout << ' ';
		if(j % 30 == 29) cout << endl;
	}
	cout << endl;
}

void Interpreter::execute(bool debug)
{
	if(debug) show_mem();
	short operand = memory[PC + 1];
	operand <<= 8;
	operand |= memory[PC + 2];
	if(operand < 0) {
		operand ^= 1 << 15;
		operand += X;
	}
	po_table[memory[PC]](operand);
	PC.address += 3;
}
