#include "table.h"

std::vector<std::vector<std::string>>& Table::getData()
{
	return data;
}

std::istream& operator>>(std::istream& in, Table& table)
{
	// TODO: реализовать вывод таблицы в DSV формате
	return in;
}

std::ostream& operator<<(std::ostream& out, Table& table)
{
	// TODO: реализовать парсинг DSV формата
	return out;
}

const int ParseError::getRowIndex() const
{
	return rowIndex;
}

const int ParseError::getValueIndex() const
{
	return valueIndex;
}

const std::string ParseError::getMessage() const
{
	return message;
}
