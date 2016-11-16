//컴파일러가 만든 .o를 실행하는 인터프리터 헤더파일 
#include"sic.h"

class Interpreter : public SIC
{
public:
	Interpreter(std::string file, bool debug, short s, short e);
	void show_mem(short start=0, short end=0);

protected:
	int start, end, data_begin;
	void load_to_memory(std::string file);
	void execute(bool debug, short s, short e);

private:
};

