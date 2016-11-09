#pragma once
#include<iostream>
#include<vector>
#include<map>

class Module
{
public:
	friend class Linker;
	Module(std::string module_name);

protected:
	Module() {}
	std::string module_name;
	short start, data, end;
	std::vector<std::pair<short, std::string>> lines;
};

class Linker : public Module
{
public:
	void operator+=(Module m);
	void link();

protected:
	std::map<std::string, short> module_address;

private:
	void write_file();
	short offset = 0;
};
