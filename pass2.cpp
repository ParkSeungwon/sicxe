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
			for(int i=0; i<stoi(s, nullptr, 16); i++) {
				f >> c;
				if(c >= 'A') cout << c - 55 << ',';
				else cout << c - '0' << ',';
			}
		}
	}
}
