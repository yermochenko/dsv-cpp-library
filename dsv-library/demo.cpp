#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "dsv/table.h"

Table create()
{
	std::string line;
	std::cout << "Enter delimeter of values in table row (enter one character and press 'Enter', or just press 'Enter' to use default value - tabulation): ";
	std::getline(std::cin, line);
	char delimeter;
	if (line.empty())
	{
		delimeter = '\t';
	}
	else if (line.size() == 1)
	{
		delimeter = line[0];
	}
	else
	{
		throw std::string("You enter more than one character");
	}
	std::cout << "Enter enclosure of values in table row (enter one character and press 'Enter', or just press 'Enter' to use default value - double quote): ";
	std::getline(std::cin, line);
	char enclosure;
	if (line.empty())
	{
		enclosure = '"';
	}
	else if (line.size() == 1)
	{
		enclosure = line[0];
	}
	else
	{
		throw std::string("You enter more than one character");
	}
	std::cout << "Choose delimeter of rows:" << std::endl;
	std::cout << "  LF (code 10 or 0x0A or \\n)" << std::endl;
	std::cout << "  CR (code 13 or 0x0D or \\r)" << std::endl;
	std::cout << "  CRLF (two characters)" << std::endl;
	std::cout << "Enter value LF, or CR, or CRLF, and press 'Enter', or just press 'Enter' to use devault value - CRLF: ";
	std::getline(std::cin, line);
	Eol eol;
	if(line == "LF")
	{
		eol = Eol::LF;
	}
	else if (line == "CR")
	{
		eol = Eol::CR;
	}
	else if (line == "CRLF" || line.empty())
	{
		eol = Eol::CRLF;
	}
	else
	{
		throw std::string("You enter invalid value");
	}
	return Table(delimeter, enclosure, eol);
}

void write()
{
	std::cout << "Demonstration of writing table into file" << std::endl;
	try
	{
		Table table = create();
		std::cout << "Enter amount of rows in table: ";
		std::string line;
		std::getline(std::cin, line);
		int n = std::stoi(line);
		std::vector<std::vector<std::string>> data;
		for (int i = 0; i < n; i++)
		{
			std::cout << "  Enter amount of values in row #" << (i + 1) << ": ";
			std::getline(std::cin, line);
			int k = std::stoi(line);
			std::vector<std::string> row;
			for (int j = 0; j < k; j++)
			{
				std::cout << "    Enter value #" << (j + 1) << ": ";
				std::getline(std::cin, line);
				row.push_back(line);
			}
			data.push_back(row);
		}
		table.getData() = data;
		std::cout << "Enter path to file to store table: ";
		std::getline(std::cin, line);
		std::ofstream fout(line, std::ios::binary);
		if (fout.is_open())
		{
			fout << table;
		}
		else
		{
			std::cout << "Can't write to file \"" << line << "\"" << std::endl;
		}
	}
	catch (std::string message)
	{
		std::cout << message << std::endl;
	}
}

int main()
{
	std::cout << "Demonstration of using DSV (Delimeter-Separated Values) library" << std::endl;
	write();
	return 0;
}
