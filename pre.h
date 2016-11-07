#include"compiler.h"

struct Macro 
{
	std::string name;
	std::vector<std::string> args;
	int start;
	int end;
};

class PreProcessor : public Compiler
{
public:
	PreProcessor(std::string filename);

protected:
	std::vector<Macro> macros;

private:
	void change(int, std::string);
	int is_macro(std::string name);
};
