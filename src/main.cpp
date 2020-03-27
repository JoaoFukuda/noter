#include <fstream>
#include <iostream>
#include <string>

char ch;

void ps_main(std::ifstream& in, std::ofstream& out);
void ps_func(std::ifstream& in, std::ofstream& out);

void call(std::string func, std::ifstream& in, std::ofstream& out);

int main(int argc, char *argv[])
{
	if(argc != 2) return 0;

	std::ifstream in (argv[1]);
	if(in.is_open())
	{
		std::ofstream out ("a.out");

		ps_main(in, out);

		out.close();
		in.close();
	}
}

void ps_main(std::ifstream& in, std::ofstream& out)
{
	bool ret = false;
	while(in >> std::noskipws >> ch)
	{
		if(ret)
		{
			ret = false;
			out << '\n';
		}

		if(ch == '#') ps_func(in, out);
		else if(ch == '\n') ret = true;
		else out << ch;
	}
}

void ps_func(std::ifstream& in, std::ofstream& out)
{
	std::string func_name;
	in >> std::noskipws >> func_name;

	call(func_name, in, out);
}

void call(std::string func_name, std::ifstream& in, std::ofstream& out)
{
	if(func_name == "insert")
	{
		std::string filename;
		in >> std::ws >> filename;

		std::ifstream other_in (filename);
		if(other_in.is_open())
		{
			ps_main(other_in, out);
			other_in.close();
		}
	} else
	{
		std::cout << "No function defined with name " << func_name << " defined. Ignoring control character..." << std::endl;
		out << '#' << func_name;
	}
}

