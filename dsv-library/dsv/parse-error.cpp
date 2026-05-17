#include "parse-error.h"

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
