#include<map>
#include<iomanip>
#include<string>
#include<fstream>
#include"sic.h"
using namespace std;

Compiler::Compiler(string file)
{
	fill_instructions(file);
	make_sym_table();
	make_obj_code();
	file.back() = 'o';
	create_object(file);
}

void Compiler::create_object(string file)
{
	ofstream f(file);
	f << "start " << hex << sym_table["start"] << endl;
	f << "data " << hex << sym_table["data_begin"] << endl;
	f << "end " << hex << sym_table["end"] << endl;
	for(auto& a : obj_code) {
		f << hex << setfill('0') << setw(4) << a.first << ' ' 
			<< hex << setfill('0') << setw(2) << +a.second.opcode 
			<< hex <<setfill('0') << setw(4) << a.second.address << endl;
	}
}

void Compiler::make_obj_code()
{
	short addr = sym_table["start"];
	bool started = false;
	for(auto& a : instructions) {
		if(addr < sym_table["data_begin"]) {
			if(started) {
				obj_code.push_back( { addr, {+op_table[a[1]], 
						is_symbol(a[2]) ? sym_table[a[2]] : stoi(a[2], nullptr, 16)}});
				addr += 3;
			}
			if(a[1] == "start") started = true;
		} 
		else if(addr == sym_table["end"]) {
			obj_code.push_back({addr, {0, 0}});
			break;
		} else {
			int k = stoi(a[2], nullptr, 16);
			if(a[1] == "word") {
				obj_code.push_back({addr, {k >> 16, k & 65535}});
				addr += 3;
			} else if(a[1] == "byte") {
				obj_code.push_back({addr, {k >> 16, k & 65535}});
				addr++;
			} else if(a[1] == "resb") {
				obj_code.push_back({addr, {0, 0}});
				addr += k;
			} else if(a[1] == "resw") {
				obj_code.push_back({addr, {0, 0}});
				addr += 3 * k;
			}
		}
	}
}

bool Compiler::is_symbol(string s)
{
	return sym_table.find(s) != sym_table.end();
}

void Compiler::make_sym_table()
{
	int addr = 0;
	bool data_begin = false;
	for(auto& a : instructions) {
		if(a[0] != "") sym_table[a[0]] = addr;
		if(a[1] == "start") {
			addr = stoi(a[2], nullptr, 16);
			sym_table["start"] = addr;
		} 
		else if(a[1] == "end") sym_table["end"] = addr;
		else if(is_opcode(a[1])) addr += 3;
		else {
			if(!data_begin) {
				sym_table["data_begin"] = addr;
				data_begin = true;
			}
			if(a[1] == "word") addr += 3;
			else if(a[1] == "byte") addr++;
			else if(a[1] == "resb") addr += stoi(a[2]);
			else if(a[1] == "resw") addr += 3 * stoi(a[2]);
		}
	}
	//for(auto& a : sym_table) cout << a.first << ' ' << hex << a.second << endl;
}

bool SIC::is_opcode(string s)
{
	return op_table.find(s) != op_table.end();
}
		
void Compiler::fill_instructions(string file)
{
	ifstream f(file);
	char c;
	string com[3];
	int n = 0;
	bool sp_flag = false;
	while(f >> noskipws >> c) {
		if(c != '\n') {
			if(c == '\t' || c == ' ') {
				if(!sp_flag) n++;
				sp_flag = true;
			} else {
				com[n] += c;
				sp_flag = false;
			}
		} else {
			instructions.push_back({com[0], com[1], com[2]});
			n = 0;
			for(int i=0; i<3; i++) com[i].clear();
		}
	}
}
