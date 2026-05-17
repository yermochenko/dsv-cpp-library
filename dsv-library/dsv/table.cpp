#include "table.h"

std::vector<std::vector<std::string>>& Table::getData()
{
	return data;
}

std::istream& operator>>(std::istream& in, Table& table)
{
	// TODO: реализовать парсинг DSV формата
	return in;
}

std::ostream& operator<<(std::ostream& out, Table& table)
{
	std::vector<std::vector<std::string>> data = table.getData();
	for (size_t i = 0, n = data.size(); i < n; i++)
	{
		for (size_t j = 0, k = data[i].size(); j < k; j++)
		{
			std::string value = data[i][j];
			bool enclosed = false;
			if (value.find(table.VALUE_DELIMETER) != std::string::npos ||
			    value.find('\r') != std::string::npos ||
				value.find('\n') != std::string::npos)
			{
				enclosed = true;
			}
			size_t pos = 0;
			while ((pos = value.find(table.VALUE_ENCLOSURE, pos)) != std::string::npos)
			{
				enclosed = true;
				value.insert(pos, 1, table.VALUE_ENCLOSURE);
				pos += 2;
			}
			if (enclosed)
			{
				out << table.VALUE_ENCLOSURE << value << table.VALUE_ENCLOSURE;
			}
			else
			{
				out << value;
			}
			if (j < k - 1)
			{
				out << table.VALUE_DELIMETER;
			}
		}
		if (i < n - 1)
		{
			switch (table.ROW_DELIMETER)
			{
			case Eol::LF:   out << '\n';   break;
			case Eol::CR:   out << '\r';   break;
			case Eol::CRLF: out << "\r\n"; break;
			}
		}
	}
	return out;
}
