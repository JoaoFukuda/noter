#include <fstream>
#include <iostream>
#include <string>

char ch;

void ps_main(std::ifstream& in, std::ofstream& out);
void ps_func(std::ifstream& in, std::ofstream& out);

void call(const std::string& func, std::ifstream& in, std::ofstream& out);

int main(int argc, char *argv[])
{
	std::string output_filename = "a.txt";
	std::string input_filename;

	for(int i = 1; i != argc; ++i)
	{
		if(argv[i][0] == '-')
		{
			if(argv[i][1] == 'o')
			{
				++i;
				output_filename = argv[i];

			}
		} else
			input_filename = argv[i];
	}

	if(input_filename.empty())
	{
		std::cout << "Could not find a suitable filename to convert" << std::endl;

		return 0;
	}

	std::ifstream in (input_filename);
	if(in.is_open())
	{
		std::ofstream out (output_filename);

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
	char ch;
	in >> std::noskipws >> ch;
	if(ch == ' ' || ch == '\t' || ch == '\r' || ch == '\n' || ch == '\0')
	{
		out << '#' << ch;
		return;
	} else
		in.putback(ch);

	std::string func_name;
	in >> std::noskipws >> func_name;

	call(func_name, in, out);
}

void call(const std::string& func_name, std::ifstream& in, std::ofstream& out)
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
		out << '#' << func_name;
}

