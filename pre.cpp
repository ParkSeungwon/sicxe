#include"pre.h"
#include<iostream>
int main(int c, char** v)
{
	if(c<3) std::cout << "usage : " << v[0] << " [infile] [outfile]" << std::endl;
	else PreProcessor{v[1], v[2]};
}
