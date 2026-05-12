#pragma once

#include <iostream>
#include <string>
#include <vector>

/*
Определяет поддерживаемый разделитель строк:
LF - символ \n (0x0A, 10)
CR - символ \r (0x0D, 13)
CRLF - пара символов \r\n
*/
enum class Eol { LF, CR, CRLF };

/*
Представляет собой таблицу, которая может быть записана в поток в формате
DSV (Delimeter Separated Values) или прочитана из потока в формате DSV
*/
class Table
{
	const char VALUE_DELIMETER;
	const char VALUE_ENCLOSURE;
	const Eol ROW_DELIMETER;
	std::vector<std::vector<std::string>> data;
public:
	/*
	Создаёт таблицу для чтения/записи табличных данных в формате DSV
	параметры - это спец. символы, используемые при форматировании таблицы
	            в DSV-формате:
	_VALUE_DELIMETER определяет разделитель между ячейками таблицы
	                 (по умолчанию разделителем является символ табуляции,
	                 что соответствует формату TSV)
	_VALUE_ENCLOSURE определяет символ-ограничитель, между парой которых
	                 заключается ячейка, содержащая спец. символы (при этом
	                 сам символ-орграничитель внутри ячейки должен быть
	                 удвоен, по умолчанию ограничителем является двойная
	                 кавычка)
	_ROW_DELIMETER   определяет разделитель строк (по умолчанию
	                 разделителем является пара символов \r\n)
	*/
	Table(
		const char _VALUE_DELIMETER = '\t',
		const char _VALUE_ENCLOSURE = '"',
		const Eol _ROW_DELIMETER = Eol::CRLF
	) : VALUE_DELIMETER(_VALUE_DELIMETER),
	    VALUE_ENCLOSURE(_VALUE_ENCLOSURE),
	    ROW_DELIMETER(_ROW_DELIMETER) {}

	/*
	возвращает текущие данные таблицы
	*/
	std::vector<std::vector<std::string>>& getData();
};

std::istream& operator>>(std::istream&, Table&);

std::ostream& operator<<(std::ostream&, Table&);
