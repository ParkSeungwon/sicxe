//컴파일러 구현부.
#include<iostream>
#include<iomanip>
#include<string>
#include<fstream>
#include"compiler.h"
using namespace std;

Compiler::Compiler(string file)
{
	fill_instructions(file);
//	for(auto& a : instructions) cout << a[0] << ' ' << a[1] << ' ' << a[2] << endl;
	make_sym_table();//PASS 1
	make_obj_code();//PASS 2
	file.back() = 'o';
	create_object(file);
	show_sym_table();
}

void Compiler::show_sym_table()
{
	multimap<short, string> m;
	for(auto a : sym_table) m.insert({a.second, a.first});
	for(auto& a : m) cout << hex << a.first << " : " << a.second << endl;
}

void Compiler::create_object(string file)
{
	ofstream f(file);
	f << "start " << hex << setfill('0') << setw(4) << sym_table["start"] << endl;
	f << "data " << hex << setfill('0') << setw(4) << sym_table["data_begin"] << endl;
	f << "end " << hex << setfill('0') << setw(4) << sym_table["end"] << endl;
	for(auto& a : obj_code) {
		f << hex << setfill('0') << setw(4) << a.first << ' ' ;
		for(auto& b : a.second) f << hex << setfill('0') << setw(2) << +b;
		f << endl;
	}
}

void Compiler::make_obj_code()
{
	short addr = sym_table["start"];
	bool started = false;
	for(auto& a : instructions) {
		if(addr < sym_table["data_begin"]) {
			if(started) {
				short two_part;
				auto pos = a[2].find(",x");
				if(pos != string::npos) {
					a[2] = a[2].erase(pos);
					two_part = (1 << 15) | sym_table[a[2]];
				} else if(is_symbol(a[2])) two_part = sym_table[a[2]];
				else {
					if(a[2] == "") two_part = 0;
					else two_part = stoi(a[2], nullptr, 16);
				}
				obj_code.push_back({addr, {+op_table[a[1]], two_part >> 8, two_part & 255}});
				addr += 3;
			}
			if(a[1] == "start") started = true;
		} else if(addr == sym_table["end"]) {
			obj_code.push_back({addr, {0}});
			break;
		} else {
			int k = a[2] == "" ? sym_table["end"] : stoi(a[2], nullptr, 16);//""->rsub
			if(a[1] == "word") {
				obj_code.push_back({addr, {k >> 16, (k >> 8) & 255, k & 255}});
				addr += 3;
			} else if(a[1] == "byte") {
				obj_code.push_back({addr, {k}});
				addr++;
			} else if(a[1] == "resb") {
				vector<unsigned char> v;
				v.resize(k);
				obj_code.push_back({addr, v});
				addr += k;
			} else if(a[1] == "resw") {
				vector<unsigned char> v;
				v.resize(3 * k);
				obj_code.push_back({addr, v});
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
{//심볼 테이블을 만든다.
	int addr = 0;//addr == LOCCTR
	bool data_begin = false;
	for(auto& a : instructions) {
		if(a[0] != "") {
			if(sym_table.find(a[0]) != sym_table.end()) throw SICException(a[0] + " symbol appears twice");
			else sym_table[a[0]] = addr;//symtab 중복체크 해야한다.
		}
		if(a[1] == "start") {
			addr = stoi(a[2], nullptr, 16);
			sym_table["start"] = addr;
		} else if(a[1] == "end") sym_table["end"] = addr;
		else if(is_opcode(a[1])) addr += 3;
		else {
			if(!data_begin) {
				sym_table["data_begin"] = addr;
				data_begin = true;
			}
			if(a[1] == "word") addr += 3;
			else if(a[1] == "byte") addr++;
			else if(a[1] == "resb") addr += stoi(a[2], nullptr, 16);
			else if(a[1] == "resw") addr += 3 * stoi(a[2], nullptr, 16);
		}
	}//return LOCCTR- starting address = program size to load to memory
}
		
void Compiler::fill_instructions(string file)
{
	ifstream f(file);
	char c;
	string com[20];
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
			sp_flag = false;
		}
	}
}
