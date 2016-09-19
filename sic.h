#include<vector>

struct Register//24 bit 
{
	char opcode;
	short address;//1 bit(direct0, indexed 1) + 15 bit address
};

//typedef char byte;//byte c'z'
//typedef char[3] word;//상수 정의 five(addr) word 5

class SIC
{
public:
	Register A, X, L, PC, SW;
	//pseudo instruction
	void start();
	void end();
	void resw();//1word space allocate
	void resb();//alpha resb 2; 2byte alloca
	
	//load and store
	void LDA(short address);
	void LDX(short); 
	void STA(short address);		
	void STX(short);
	
	//arithmetic
	void ADD(); 
	void SUB(); 
	void MUL(); 
	void DIV();
	
	//comparison
	void COMP(); 

	//conditional jump
	void JLT(); 
	void JEQ(); 
	void JGT();

	//subroutine linkage
	void JSUB(); 
	void RSUB();

	//IO. test divice. read write device
	void TD();
	void RD();
	void WD();

protected:
	char memory[32768];//2**15
	bool is_opcode(std::string s);
	std::map<std::string, char> op_table = {{"lda", 0x00}, {"sta", 0x0c}};

private:
};


class Compiler : public SIC
{
public:
	Compiler(std::string filename);
	void make_sym_table();
	void make_obj_code();
	bool is_symbol(std::string s);
	void create_object(std::string file);

protected:
	std::map<std::string, short> sym_table;
	std::vector<std::array<std::string, 3>> instructions;
	std::vector<std::pair<short, Register>> obj_code;
	void fill_instructions(std::string file);
};

