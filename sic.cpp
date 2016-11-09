#include<iostream>
using namespace std;

int main(int c, char** v) 
{
	for(int i=1; i<c; i++) {
		string s;
		s = s + "./pre.x " + v[i] + " /tmp/" + v[i];
		cout << s << endl;
		system(s.data());
		s.clear();
		s = s + "./compile.x /tmp/" + v[i] + ' ' + v[i];
		s.back() = 'o';
		cout << s << endl;
		system(s.data());
	}
	string s{"./linker.x "};
	for(int i=1; i<c; i++) {
		s += v[i];
		s.erase(s.find_last_of('.'));
		s += ' ';
	}
	system(s.data());
	cout << s << endl;
	s = "./run.x ";
	s += v[1];
	s.back() = 'x';
	cout << s << endl;
	system(s.data());
//	for(int i=1; i<=c; i++) system("./compile.x /tmp/"v[i] 
}
