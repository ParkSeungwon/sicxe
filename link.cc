#include"link.h"
#include<fstream>
#include<iomanip>
#include<string>
#include<sstream>
using namespace std;

void Linker::operator+=(Module m)
{
	if(lines.empty()) {
		module_num = m.module_num;
		start = m.start;
		data = m.data;
		end = m.end;
	} else {
		offset = end + 1 - m.start;
		module_address[m.module_num] = end + 1;
		end += 1 + m.end - m.start;
	}
	for(auto& a : m.lines) {
		if(a.first == m.data) break;
		stringstream ss;
		ss << a.second;
		char c[2];
		ss >> c[0] >> c[1];
		short operand;
		ss >> hex >> operand;
		ss.clear();
		ss << c[0] << c[1];
		if(operand >= start) {
			operand += offset;
			ss << setfill('0') << setw(4) << hex << operand;
		} else {//매우 제한적이지만 오브젝트파일은 숫자로 이름을 지어야 한다.
			//그리고 그 파일명이 스타트 번지보다 작아야 한다.
			//링커에 첫번째 매개변수로 들어오는 파일이 메인이 된다.
			//서브루틴은 오브젝트파일의 숫자를 오퍼란드로 한다.
			//이 부분은 서브루틴이라고 마크하는 부분이다.
			ss << '<' << setfill('0') << setw(2) << hex << operand << '>';
		}
		ss >> a.second;
	}
	for(auto& a : m.lines) a.first += offset;
	lines.insert(lines.end(), m.lines.begin(), m.lines.end());
}

void Linker::link()
{
	for(auto& a : lines) {
		char c[3] {};
		if(a.second[2] == '<') {
			c[0] = a.second[3];
			c[1] = a.second[4];
			short jump_address = module_address[atoi(c)];
			stringstream ss;
			ss << setw(4) << hex << setfill('0') << jump_address;
			a.second.replace(2, 4, ss.str());
		}
	}
	write_file();
}

void Linker::write_file()
{
	ofstream f(to_string(module_num) + ".x");
	f << "start " << hex << start << endl << "data " << hex << data << endl << "end " << hex << end << endl;
	for(auto& a : lines) f << hex << setw(4) << setfill('0') << a.first << ' ' << a.second << endl;
}


Module::Module(int num)
{
	ifstream f(to_string(num) + ".o");
	string s;
	module_num = num;
	f >> s >> hex >> start >> s >> hex >> data >> s >> hex >> end;
	short addr;
	while(f >> hex >> addr) {
		f >> s;
		lines.push_back({addr, s});
	}
}

