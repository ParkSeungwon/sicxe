#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>
using namespace std;

vector<array<string, 3>> instructions;
struct Macro 
{
	std::string name;
	std::vector<std::string> args;
	int start;
	int end;
};

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
	ofstream of("Int");
	
	//라벨과 코드 오퍼란드 구분하는 부분
	char c;
	string com[30];
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

	Macro m;
	vector<Macro> macros;
	for(int i=0; i<instructions.size(); i++) {
		if(instructions[i][1] == "macro") {
			m.name = instructions[i][0];
			string s;
			stringstream ss{instructions[i][2]};
			while(getline(ss, s, ',')) m.args.push_back(s);//extract arguments
			m.start = i;
		} else if(instructions[i][1] == "mend\r") {
			m.end = i;
			macros.push_back(m);
		}
	}
	for(auto& a : macros) {
		cout << "macro name : " << a.name << endl;
		for(int i=a.start; i<a.end; i++) {
			for(auto& b : instructions[i]) cout << b << ' ';
			cout << endl;
		}
	}

}
