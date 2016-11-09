#include<iostream>
#include<iomanip>
#include<fstream>
#include<sstream>
using namespace std;

int main(int argc, char** v)
{
	ifstream f(v[1]);
	char c;
	while(f >> c) {
		string s;
		if(c == 'T') {
			cout << "TAG : " << c;
			f >> setw(6) >> s;
			cout << ", ADDR : " << s;
			f >> setw(2) >> s;
			cout << ", LEN : " << s << endl;
			char ch[stoi(s, nullptr, 16)];
			for(int i=0; i<stoi(s, nullptr, 16); i++) f >> ch[i];
			cout << "CODE : ";
			for(auto& a : ch) cout << a;
			cout << "\nHCODE : ";
			for(auto& a : ch) {
				if(a >= 'A') cout << a - 55 << ',';
				else cout << a - '0' << ',';
			}
			cout << endl;
		}
	}
}
