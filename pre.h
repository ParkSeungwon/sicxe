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
	PreProcessor(std::string filename, std::string outfile);

protected:
	std::vector<Macro> macros;

private:
	std::vector<std::array<std::string, 3>> change(int, std::string) const;
	int is_macro(std::string name) const;
};
