//컴파일러 헤더파일. 소오스를 .o로 만든다.
#include"sic.h"

class Compiler : public SIC
{
public:
	Compiler(std::string filename);

protected:
	Compiler() {}
	void make_sym_table();//PASS 1
	void make_obj_code();//PASS 2
	bool is_symbol(std::string s);
	void create_object(std::string file);
	void fill_instructions(std::string file);
	void show_sym_table();

	std::map<std::string, short> sym_table;
	std::vector<std::array<std::string, 3>> instructions;
	std::vector<std::pair<short, std::vector<unsigned char>>> obj_code;
};

