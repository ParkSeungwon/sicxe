#pragma once
#include<iostream>
#include<vector>
#include<map>

class Module
{
public:
	friend class Linker;
	Module(int module_num);

protected:
	Module() {}
	short module_num, start, data, end;
	std::vector<std::pair<short, std::string>> lines;
};

class Linker : public Module
{
public:
	void operator+=(Module m);
	void link();

protected:
	std::map<short, short> module_address;

private:
	void write_file();
	short offset = 0;
};
