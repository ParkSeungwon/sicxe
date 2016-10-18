#include"link.h"
using namespace std;

int main(int c, char** v)
{
	Linker lnk;
	for(int i=1; i<c; i++) lnk += Module(atoi(v[i]));
	lnk.link();
}
