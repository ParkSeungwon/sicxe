#include"pre.h"
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;

PreProcessor::PreProcessor(string file, string out)
{
	fill_instructions(file);

	for(int i=0; i<instructions.size(); i++) {//byte C'A' 처리
		if((instructions[i][1] == "byte" || instructions[i][1] == "BYTE") 
				&& instructions[i][2][1] == '\'') {
			vector<array<string, 3>> v;
			stringstream ss;
			char c;
			ss << instructions[i][2];
			ss >> c >> c >> c;
			while(c != '\'') {
				stringstream ss2;
				ss2 << hex << (c - '\0');
				string s;
				ss2 >> s; 
				if(v.empty()) v.push_back({instructions[i][0], "byte", s});
				else v.push_back({"", "byte", s});
				ss >> noskipws >> c;
			}
			instructions.erase(instructions.begin() + i);
			instructions.insert(instructions.begin() + i, v.begin(), v.end());
		}
	}

	for(auto& a : instructions) for(auto& b : a) for(auto& c : b) c = tolower(c);
	
	Macro m;
	for(int i=0; i<instructions.size(); i++) {
		if(instructions[i][0] == "macro") {
			m.name = instructions[i][1];
			string s;
			stringstream ss{instructions[i][2]};
			while(getline(ss, s, ',')) m.args.push_back(s);//extract arguments
			m.start = i;
		} else if(instructions[i][0] == "mend") {
			m.end = i;
			macros.push_back(m);
			m.args.clear();
		}
		int idx = is_macro(instructions[i][1]);
		if(idx >= 0) {
			auto v = change(idx, instructions[i][2]);//argument replace
			instructions.erase(instructions.begin() + i);//sentence insert
			instructions.insert(instructions.begin() + i, v.begin(), v.end());
		}
	}
	
	int deleted_lines = 0;
	for(auto& a : macros) {//strip definition part
		instructions.erase(instructions.begin() + a.start - deleted_lines, 
				instructions.begin() + a.end + 1 - deleted_lines);
		deleted_lines += a.end - a.start + 1;
	}
		
	
	ofstream f(out);//write to file
	for(auto& a : instructions) f << a[0] << ' ' << a[1] << ' ' << a[2] << endl;
}

int PreProcessor::is_macro(string name) const
{
	for(int i=0; i<macros.size(); i++) if(macros[i].name == name) return i;
	return -1;
}

vector<array<string, 3>> PreProcessor::change(int idx, string args) const
{
	stringstream ss{args};
	string s;
	vector<string> v;
	while(getline(ss, s, ',')) v.push_back(s);

	vector<array<string, 3>> r;
	r.insert(r.begin(), instructions.begin() + macros[idx].start + 1,
			instructions.begin() + macros[idx].end);
	for(auto& a : r) 
		for(int i=0; i<macros[idx].args.size(); i++) 
			for(int j=0; j<3; j++) if(a[j] == macros[idx].args[i]) a[j] = v[i];
	return r;	
}

