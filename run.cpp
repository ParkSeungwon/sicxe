#include<iostream>
#include"interpreter.h"
using namespace std;

int main(int c, char** v)
{
	if(c < 2) {
		cout << "usage : " << v[0] << " [file to run .o]" << endl;
		return 0;
	}
	Interpreter inter(v[1]);
}
