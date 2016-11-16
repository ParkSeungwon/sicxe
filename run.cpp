#include<iostream>
#include"interpreter.h"
using namespace std;

int main(int c, char** v)
{
	if(c < 2) {
		cout << "usage : " << v[0] << " [file to run .o]" << endl;
		return 0;
	}
	bool debug = c >= 3 ? true : false;
	short s = 0, e = 0;
	if(c == 4) {
		s = stoi(v[2], nullptr, 16);
		e = stoi(v[3], nullptr, 16);
	}
	Interpreter inter(v[1], debug, s, e);
}
