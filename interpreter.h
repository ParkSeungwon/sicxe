#include"sic.h"

class Interpreter : public SIC
{
public:
	Interpreter(std::string file);
	void show_mem();

protected:
	int start, end, data_begin;
	void load_to_memory(std::string file);
	void execute();

private:
	void fetch();
};

