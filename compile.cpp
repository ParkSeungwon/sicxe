#include<map>
#include<vector>
#include<fstream>
#include<iostream>
#include"sic.h"
using namespace std;

int main(int argc, char** argv)
{
	if(argc < 2) {
		cout << "usage : " << argv[0] << "[file to compile]" << endl;
		return 0;
	}
	Compiler cp(argv[1]);
}

