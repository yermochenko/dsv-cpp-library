#pragma once

#include <iostream>
#include <string>
#include <vector>

/**
Определяет поддерживаемый разделитель строк:
LF - символ \n (0x0A, 10)
CR - символ \r (0x0D, 13)
CRLF - пара символов \r\n
*/
enum class Eol { LF, CR, CRLF };

/**
Представляет собой таблицу, которая может быть записана в поток в формате
DSV (Delimeter Separated Values) или прочитана из потока в формате DSV
*/
class Table
{
	std::vector<std::vector<std::string>> data;
public:
	/**
	Разделитель между ячейками таблицы (по умолчанию - символ табуляции, что
	соответствует формату TSV)
	*/
	const char VALUE_DELIMETER;
	/**
	Символ-ограничитель, между парой которых заключается ячейка, содержащая
	спец. символы (по умолчанию ограничителем является двойная кавычка)
	*/
	const char VALUE_ENCLOSURE;
	/**
	Определяет разделитель строк (по умолчанию разделителем является пара
	символов \r\n - значение Eol::CRLF)
	*/
	const Eol ROW_DELIMETER;

	/**
	Создаёт таблицу для чтения/записи табличных данных в формате DSV.
	Параметры - это спец. символы, используемые при форматировании таблицы
	в DSV-формате.
	\param[in] _VALUE_DELIMETER Определяет разделитель между ячейками таблицы
	                            (по умолчанию разделителем является символ
	                            табуляции, что соответствует формату TSV)
	\param[in] _VALUE_ENCLOSURE Определяет символ-ограничитель, между парой
	                            которых заключается ячейка, содержащая спец.
	                            символы (при этом сам символ-орграничитель
	                            внутри ячейки должен быть удвоен, по умолчанию
	                            ограничителем является двойная кавычка)
	\param[in] _ROW_DELIMETER   Определяет разделитель строк (по умолчанию
	                            разделителем является пара символов \r\n)
	*/
	Table(
		const char _VALUE_DELIMETER = '\t',
		const char _VALUE_ENCLOSURE = '"',
		const Eol _ROW_DELIMETER = Eol::CRLF
	) : VALUE_DELIMETER(_VALUE_DELIMETER),
	    VALUE_ENCLOSURE(_VALUE_ENCLOSURE),
	    ROW_DELIMETER(_ROW_DELIMETER) {}

	/**
	\return Возвращает текущие данные таблицы
	*/
	std::vector<std::vector<std::string>>& getData();
};

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

/**
Выполняет чтение данных из потока, разбор (парсинг) этих данных в формате DSV и
сохранение данных в указанную таблицу (объект класса Table)
\throw ParseError В случае, когда входной поток содержит некорректные данные не
                  соответствующие формату DSV (в соответствии с натройками
                  переданного объекта класса Table)
*/
std::istream& operator>>(std::istream&, Table&);

std::ostream& operator<<(std::ostream&, Table&);
