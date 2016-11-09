//sic/xe simulator 헤더파일입니다.
#include<vector>
#include<functional>
#include<string>
#include<map>

struct Register//24 bit 
{
	unsigned char opcode;
	short address;//1 bit(direct0, indexed 1) + 15 bit address
	Register& operator=(int n);
	operator int(); 
};

class SICException : public std::exception
{
public:
	SICException(std::string s) : message(s) {}
	virtual const char* what() const throw() {
		return message.data();
	}
protected:
	std::string message;
};

//typedef char byte;//byte c'z'
//typedef char[3] word;//상수 정의 five(addr) word 5

class SIC
{
public:
	Register A, X, L, PC, SW;

protected:
	unsigned char memory[32768];//2**15
	bool is_opcode(std::string s);
	int fetch(short addr) const;

	std::map<std::string, unsigned char> op_table = {
		{"lda", 0x00}, {"ldx", 0x04}, {"ldl", 0x08},
		{"sta", 0x0c}, {"stx", 0x10}, {"stl", 0x14},
		{"add", 0x18}, {"sub", 0x1c}, {"mul", 0x20}, {"div", 0x24},
		{"comp", 0x28}, {"tix", 0x2c},
		{"jeq", 0x30}, {"jgt", 0x34}, {"jlt", 0x38}, {"j", 0x3c},
		{"jsub", 0x48}, {"rsub", 0x4c}, 
		{"ldch", 0x50}, {"stch", 0x54},
		{"rd", 0xd8}, {"wd", 0xdc}, {"td", 0xe0}
	};

	std::map<unsigned char, std::function<void(short)>> po_table = {
		{0x00, std::bind(&SIC::LDA, this, std::placeholders::_1)},
		{0x04, std::bind(&SIC::LDX, this, std::placeholders::_1)},
		{0x08, std::bind(&SIC::LDL, this, std::placeholders::_1)},
		{0x0c, std::bind(&SIC::STA, this, std::placeholders::_1)},
		{0x10, std::bind(&SIC::STX, this, std::placeholders::_1)},
		{0x14, std::bind(&SIC::STL, this, std::placeholders::_1)},
		{0x18, std::bind(&SIC::ADD, this, std::placeholders::_1)},
		{0x1c, std::bind(&SIC::SUB, this, std::placeholders::_1)},
		{0x20, std::bind(&SIC::MUL, this, std::placeholders::_1)},
		{0x24, std::bind(&SIC::DIV, this, std::placeholders::_1)},
		{0x28, std::bind(&SIC::COMP, this, std::placeholders::_1)},
		{0x2c, std::bind(&SIC::TIX, this, std::placeholders::_1)},
		{0x30, std::bind(&SIC::JEQ, this, std::placeholders::_1)},
		{0x34, std::bind(&SIC::JGT, this, std::placeholders::_1)},
		{0x38, std::bind(&SIC::JLT, this, std::placeholders::_1)},
		{0x3c, std::bind(&SIC::J, this, std::placeholders::_1)},
		{0x48, std::bind(&SIC::JSUB, this, std::placeholders::_1)},
		{0x4c, std::bind(&SIC::RSUB, this, std::placeholders::_1)},
		{0xd8, std::bind(&SIC::RD, this, std::placeholders::_1)},
		{0xdc, std::bind(&SIC::WD, this, std::placeholders::_1)},
		{0xe0, std::bind(&SIC::TD, this, std::placeholders::_1)},
		{0x50, std::bind(&SIC::LDCH, this, std::placeholders::_1)},
		{0x54, std::bind(&SIC::STCH, this, std::placeholders::_1)}
	};

private:
	//pseudo instruction
	void start();
	void end();
	void resw();//1word space allocate
	void resb();//alpha resb 2; 2byte alloca
	
	//load and store
	void LDA(short address);
	void LDX(short); 
	void LDL(short); 
	void STA(short address);		
	void STX(short);
	void STL(short); 
	
	//arithmetic
	void ADD(short); 
	void ADDX(short);
	void SUB(short); 
	void MUL(short); 
	void DIV(short);
	
	//comparison
	void COMP(short); 
	void TIX(short);

	//conditional jump
	void JLT(short); 
	void JEQ(short); 
	void JGT(short);
	void J(short);

	//subroutine linkage
	void JSUB(short); 
	void RSUB(short);

	//IO. test divice. read write device
	void TD(short);
	void RD(short);
	void WD(short);

	//char handle
	void LDCH(short);
	void STCH(short);
};

