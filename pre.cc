#include"pre.h"
#include<fstream>
#include<sstream>
#include<iostream>
using namespace std;

PreProcessor::PreProcessor(string file)
{
	fill_instructions(file);
	for(auto& a : instructions) 
		if(a[1] == "byte" && (a[2][0] == 'C' || a[2][0] == 'c')) 
			a[2] = to_string(a[2][2]-'\0'); 
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
		}
		int idx = is_macro(instructions[i][1]);
		if(idx >= 0) {
			change(idx, instructions[i][2]);//argument replace
			instructions.erase(instructions.begin() + i);//sentence insert
			instructions.insert(instructions.begin() + i, 
					instructions.begin() + macros[idx].start + 1,
					instructions.begin() + macros[idx].end);
		}
	}
	for(auto& a : macros) //strip definition part
		instructions.erase(instructions.begin() + a.start, 
				instructions.begin() + a.end + 1);
	ofstream f(file + ".s");//write to file
	for(auto& a : instructions) f << a[0] << ' ' << a[1] << ' ' << a[2] << endl;
}

int PreProcessor::is_macro(string name)
{
	for(int i=0; i<macros.size(); i++) if(macros[i].name == name) return i;
	return -1;
}

void PreProcessor::change(int idx, string args)
{
	stringstream ss{args};
	string s;
	vector<string> v;
	while(getline(ss, s, ',')) v.push_back(s);
	for(int i=macros[idx].start+1; i<macros[idx].end; i++) {
		for(int j=0; j<macros[idx].args.size(); j++) {
			for(int k=0; k<3; k++) {
				if(instructions[i][k] == macros[idx].args[j])
					instructions[i][k] = v[j];
			}
		}
	}
	macros[idx].args = v;
}

