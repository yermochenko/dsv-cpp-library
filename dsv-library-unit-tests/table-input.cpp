#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <sstream>
#include "../dsv-library/dsv/table.h"

#define ERROR_MESSAGE_MAX_LENGTH 1000

void assertTablesAreEqual(const std::vector<std::vector<std::string>>& expected, const std::vector<std::vector<std::string>>& actual);

namespace DsvLibraryUnitTests
{
	TEST_CLASS(TableInputUnitTests)
	{
	public:
		TEST_METHOD(test01)
		{
			std::istringstream sin("123\tabc\r\n456\txyz\r\n789\tmnk");
			Table table;
			sin >> table;
			assertTablesAreEqual({
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk"}
			}, table.getData());
		}
		TEST_METHOD(test02)
		{
			std::istringstream sin("123;abc\r\n456;xyz\r\n789;\"mnk; pqr; uvw\"");
			Table table(';');
			sin >> table;
			assertTablesAreEqual({
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk; pqr; uvw"}
			}, table.getData());
		}
		TEST_METHOD(test03)
		{
			std::istringstream sin("123\tabc\txyz\r\n456\r\n789\t'mnk, ''pqr'', uvw'");
			Table table('\t', '\'');
			sin >> table;
			assertTablesAreEqual({
				{"123", "abc", "xyz"},
				{"456"},
				{"789", "mnk, 'pqr', uvw"}
			}, table.getData());
		}
		TEST_METHOD(test04)
		{
			std::istringstream sin("123,abc\r\n456,xyz\r\n789,'mnk, ''pqr'', uvw'");
			Table table(',', '\'');
			sin >> table;
			assertTablesAreEqual({
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk, 'pqr', uvw"}
			}, table.getData());
		}
		TEST_METHOD(test05)
		{
			std::istringstream sin("123;abc\n456;xyz\n789;'mnk,\npqr,\nuvw'");
			Table table(';', '\'', Eol::LF);
			sin >> table;
			assertTablesAreEqual({
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk,\npqr,\nuvw"}
			}, table.getData());
		}
		TEST_METHOD(test06)
		{
			std::istringstream sin("123;abc\r456;xyz\r789;\"mnk;\rpqr;\ruvw\"");
			Table table(';', '"', Eol::CR);
			sin >> table;
			assertTablesAreEqual({
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk;\rpqr;\ruvw"}
			}, table.getData());
		}
		TEST_METHOD(test07)
		{
			std::istringstream sin("123\tabc\n456\txyz\n789\t\"mnk,\n\"\"pqr\"\",\nuvw\"");
			Table table('\t', '"', Eol::LF);
			sin >> table;
			assertTablesAreEqual({
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk,\n\"pqr\",\nuvw"}
			}, table.getData());
		}
		TEST_METHOD(test08)
		{
			std::istringstream sin("123\tabc\r\n456\txyz\r\n789\t\"mnk\t\"\"pqr\"\"\r\nuvw\"");
			Table table('\t', '"', Eol::CRLF);
			sin >> table;
			assertTablesAreEqual({
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk\t\"pqr\"\r\nuvw"}
			}, table.getData());
		}
		TEST_METHOD(test09)
		{
			std::istringstream sin("123;abc\r\n456;xyz\r\n789;\"mnk;\n\"\"pqr\"\";\nuvw\"");
			Table table(';');
			sin >> table;
			assertTablesAreEqual({
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk;\n\"pqr\";\nuvw"}
			}, table.getData());
		}
		TEST_METHOD(test10)
		{
			std::istringstream sin("123;abc\r\n\r\n456;xyz\r\n789;mnk");
			Table table(';');
			sin >> table;
			assertTablesAreEqual({
				{"123", "abc"},
				{},
				{"456", "xyz"},
				{"789", "mnk"}
			}, table.getData());
		}
		TEST_METHOD(test11)
		{
			std::istringstream sin("123;abc\r\n456;;xyz\r\n789;mnk");
			Table table(';');
			sin >> table;
			assertTablesAreEqual({
				{"123", "abc"},
				{"456", "", "xyz"},
				{"789", "mnk"}
			}, table.getData());
		}

		TEST_METHOD(test12)
		{
			std::istringstream sin("\r\n123;abc\r\n456;xyz\r\n789;mnk");
			Table table(';');
			sin >> table;
			assertTablesAreEqual({
				{},
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk"}
			}, table.getData());
		}
		TEST_METHOD(test13)
		{
			std::istringstream sin("123;abc\r\n;456;xyz\r\n789;mnk");
			Table table(';');
			sin >> table;
			assertTablesAreEqual({
				{"123", "abc"},
				{"", "456", "xyz"},
				{"789", "mnk"}
			}, table.getData());
		}
		TEST_METHOD(test14)
		{
			std::istringstream sin("123;abc\r\n456;xyz\r\n789;\"mnk;\n\"\"pqr\"\";\nuvw\"\r\n");
			Table table(';');
			sin >> table;
			assertTablesAreEqual({
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk;\n\"pqr\";\nuvw"}
			}, table.getData());
		}
		TEST_METHOD(test15)
		{
			std::istringstream sin("123;abc\r\n456;xyz;\r\n789;\"mnk;\n\"\"pqr\"\";\nuvw\"");
			Table table(';');
			sin >> table;
			assertTablesAreEqual({
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk;\n\"pqr\";\nuvw"}
			}, table.getData());
		}
		TEST_METHOD(test16)
		{
			auto code = []()
			{
				std::istringstream sin("123;abc\r\n456;xyz\r;789;mnk");
				Table table(';');
				sin >> table;
			};
			Assert::ExpectException<ParseError>(code);
		}
		TEST_METHOD(test17)
		{
			auto code = []()
			{
				std::istringstream sin("123;abc\r\n456;xyz\r\"789;mnk\"");
				Table table(';');
				sin >> table;
			};
			Assert::ExpectException<ParseError>(code);
		}
		TEST_METHOD(test18)
		{
			auto code = []()
			{
				std::istringstream sin("123;abc\r\n456;xyz\r\r789;mnk");
				Table table(';');
				sin >> table;
			};
			Assert::ExpectException<ParseError>(code);
		}
		TEST_METHOD(test19)
		{
			auto code = []()
			{
				std::istringstream sin("123;abc\r\n456;xyz\r789;mnk");
				Table table(';');
				sin >> table;
			};
			Assert::ExpectException<ParseError>(code);
		}
		TEST_METHOD(test20)
		{
			auto code = []()
			{
				std::istringstream sin("123;abc\r\n456;xyz\r\n789;mnk, \"pqr\", uvw");
				Table table(';');
				sin >> table;
			};
			Assert::ExpectException<ParseError>(code);
		}
		TEST_METHOD(test21)
		{
			auto code = []()
			{
				std::istringstream sin("123;abc\n456;xyz\n789;mnk,\rpqr,\ruvw");
				Table table(';', '"', Eol::LF);
				sin >> table;
			};
			Assert::ExpectException<ParseError>(code);
		}
		TEST_METHOD(test22)
		{
			auto code = []()
			{
				std::istringstream sin("123;abc\r\n456;xyz\r\n789;mnk,\npqr,\nuvw");
				Table table(';');
				sin >> table;
			};
			Assert::ExpectException<ParseError>(code);
		}
		TEST_METHOD(test23)
		{
			auto code = []()
			{
				std::istringstream sin("123;abc\n456;xyz\n789;\rmnk");
				Table table(';', '"', Eol::LF);
				sin >> table;
			};
			Assert::ExpectException<ParseError>(code);
		}
		TEST_METHOD(test24)
		{
			auto code = []()
			{
				std::istringstream sin("123;abc\r\n456;xyz\r\n789;\nmnk");
				Table table(';');
				sin >> table;
			};
			Assert::ExpectException<ParseError>(code);
		}
		TEST_METHOD(test25)
		{
			auto code = []()
			{
				std::istringstream sin("123;abc\n456;\"xyz;pqr\"\r\n789;mnk");
				Table table(';', '"', Eol::LF);
				sin >> table;
			};
			Assert::ExpectException<ParseError>(code);
		}
		TEST_METHOD(test26)
		{
			auto code = []()
			{
				std::istringstream sin("123;abc\r\n456;\"xyz;pqr\"\n789;mnk");
				Table table(';');
				sin >> table;
			};
			Assert::ExpectException<ParseError>(code);
		}
		TEST_METHOD(test27)
		{
			auto code = []()
			{
				std::istringstream sin("123;abc\r\n456;\"xyz, \"\"pqr\", uvw\"\r\n789;mnk");
				Table table(';');
				sin >> table;
			};
			Assert::ExpectException<ParseError>(code);
		}
	};
}

void assertTablesAreEqual(const std::vector<std::vector<std::string>>& expected, const std::vector<std::vector<std::string>>& actual)
{
	wchar_t message[ERROR_MESSAGE_MAX_LENGTH];
	Assert::AreEqual(expected.size(), actual.size(), L"Rows amount are different");
	for (size_t i = 0, n = expected.size(); i < n; i++)
	{
		swprintf(message, ERROR_MESSAGE_MAX_LENGTH, L"Values amount are different in row %zd", i);
		Assert::AreEqual(expected[i].size(), actual[i].size(), message);
		for (size_t j = 0, k = expected[i].size(); j < k; j++)
		{
			swprintf(message, ERROR_MESSAGE_MAX_LENGTH, L"Values with indexes [%zd, %zd] are different", i, j);
			Assert::AreEqual(expected[i][j], actual[i][j], message);
		}
	}
}
