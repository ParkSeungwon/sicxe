#include"sic.h"

class Compiler : public SIC
{
public:
	Compiler(std::string filename);

protected:
	void make_sym_table();
	void make_obj_code();
	bool is_symbol(std::string s);
	void create_object(std::string file);
	void fill_instructions(std::string file);

	std::map<std::string, short> sym_table;
	std::vector<std::array<std::string, 3>> instructions;
	std::vector<std::pair<short, Register>> obj_code;
};

