#include<iostream>
#include<iomanip>
#include<fstream>
#include<vector>
#include<map>
using namespace std;

vector<array<string, 3>> instructions;

std::map<std::string, unsigned char> op_table = {
	{"lda", 0x00}, {"ldx", 0x04}, {"sta", 0x0c}, {"stx", 0x10},
	{"add", 0x18}, {"sub", 0x1c}, {"mul", 0x20}, {"div", 0x24},
	{"comp", 0x28}, {"jeq", 0x30}, {"jgt", 0x34}, {"jlt", 0x38},
	{"jsub", 0x48}, {"rsub", 0x4c},
	{"rd", 0xd8}, {"wd", 0xdc}, {"td", 0xe0},
	{"ldch", 0x50}, {"stch", 0x54}, {"addx", 0x19}
};

bool is_opcode(string s)
{
	return op_table.find(s) != op_table.end();
}

int main(int argc, char** v)
{
	ifstream f(v[1]);
	ofstream of(v[2]);
	ofstream lf("tmp");
	
	//라벨과 코드 오퍼란드 구분하는 부분
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
			sp_flag = false;
		}
	}
	for(auto& a : instructions) {
		of << a[0] << ' ' << a[1] << ' ' << a[2] << endl;
	}

	//symtab 생성 부분
	map<string, short> sym_table;

	int addr = 0;//addr == LOCCTR
	bool data_begin = false;
	for(auto& a : instructions) {
		if(a[0] != "") {
			sym_table[a[0]] = addr;
		}
		if(a[1] == "start") {
			addr = stoi(a[2], nullptr, 16);
			sym_table["start"] = addr;
		} else if(a[1] == "end") sym_table["end"] = addr;
		else if(is_opcode(a[1])) {//opcode일 경우
			lf << hex << addr << ' ' << hex << +op_table[a[1]] << ' ' << hex << a[2] << endl; 
			addr += 3;
		} else {
			if(!data_begin) {
				sym_table["data_begin"] = addr;
				data_begin = true;
			}
			if(a[1] == "word") addr += 3;
			else if(a[1] == "byte") addr++;
			else if(a[1] == "resb") addr += stoi(a[2]);
			else if(a[1] == "resw") addr += 3 * stoi(a[2]);
		}
	}//return LOCCTR- starting address = program size to load to memory
	lf.close();
	f.close();
	of.close();

	ifstream ft("tmp");
	ofstream ff(v[3]);
	string s[3];
	ff << "LCTR CD ADDR\n" ;
	while(ft >> s[0] >> s[1] >> s[2]) {
		ff << s[0] << ' ' << setw(2) << setfill('0') << s[1] << ' ';
		ff << hex << sym_table[s[2]] << endl;
	}
}
