#pragma once

/**
Определяет поддерживаемый разделитель строк:
LF - символ \n (0x0A, 10)
CR - символ \r (0x0D, 13)
CRLF - пара символов \r\n
*/
enum class Eol { LF, CR, CRLF };
