#include"link.h"
#include<fstream>
#include<iomanip>
#include<string>
#include<sstream>
using namespace std;

void Linker::operator+=(Module m)
{
	if(lines.empty()) {
		module_name = m.module_name;
		start = m.start;
		data = m.data;
		end = m.end;
	} else {
		offset = end + 1 - m.start;
		module_address[m.module_name] = end + 1;
		end += 1 + m.end - m.start;
	}
	for(auto& a : m.lines) {
		if(a.first == m.data) break;
		stringstream ss;
		ss << a.second;
		char c[2];
		ss >> c[0] >> c[1];
		if(c[0] == '4' && c[1] == '8') {
			a.second.insert(2, 1, '<');
			continue;//jsub : does not change a.second
		}
		int operand;
		ss >> hex >> operand;
		ss.clear();
		ss << c[0] << c[1];//insert opcode
		if(operand >= start) {
			operand += offset;//change offset
			ss << setfill('0') << setw(4) << hex << operand;
		}
		ss >> a.second;
	}
	for(auto& a : m.lines) a.first += offset;
	lines.insert(lines.end(), m.lines.begin(), m.lines.end());
}

void Linker::link()
{
	for(auto& a : lines) {
		if(a.second[0] == '4' && a.second[1] == '8' && a.second[2] == '<') {
			stringstream ss2;
			ss2 << a.second;
			string s, file;
			ss2 >> setw(3) >> s;
			while (ss2 >> setw(2) >> s) file += (char)stoi(s, nullptr, 16);
			short jump_address = module_address[file];
			stringstream ss;
			ss << setw(4) << hex << setfill('0') << jump_address;
			a.second.replace(2, string::npos, ss.str());
		}
	}
	write_file();
}

void Linker::write_file()
{
	ofstream f(module_name + ".x");
	f << "start " << hex << start << endl << "data " << hex << data << endl << "end " << hex << end << endl;
	for(auto& a : lines) f << hex << setw(4) << setfill('0') << a.first << ' ' << a.second << endl;
}


Module::Module(string file)
{
	ifstream f(file + ".o");
	string s;
	module_name = file;
	f >> s >> hex >> start >> s >> hex >> data >> s >> hex >> end;
	short addr;
	while(f >> hex >> addr) {
		f >> s;
		lines.push_back({addr, s});
	}
}

