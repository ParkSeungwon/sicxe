#include<iostream>
#include"compiler.h"
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 3) {
		cout << "usage : " << argv[0] << "[file to compile] [file out]" << endl;
		return 0;
	}
	Compiler cp(argv[1], argv[2]);
}

