#pragma once

#include <string>

/**
Представляет собой ошибку, которая может возникнуть при разборе потока символов
в формате DSV
*/
class ParseError
{
	const int rowIndex;
	const int valueIndex;
	const std::string message;
public:
	/**
	Создаёт ошибку, возникшую при разборе (парсинге) входного потока (файла)
	в формате DSV
	\param[in] _rowIndex   Индекс строки во входном потоке, содержащей ошибочный
						   символ
	\param[in] _valueIndex Индекс значения (ячейки) в строке, содержащего
						   ошибочный символ
	\param[in] _message    Текстовое описание возникшей ошибки
	*/
	ParseError(
		const int _rowIndex,
		const int _valueIndex,
		const std::string _message
	) : rowIndex(_rowIndex),
		valueIndex(_valueIndex),
		message(_message) {}
	const int getRowIndex() const;
	const int getValueIndex() const;
	const std::string getMessage() const;
};
