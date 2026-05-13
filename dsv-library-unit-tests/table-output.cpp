#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

#include <sstream>
#include "../dsv-library/dsv/table.h"

namespace DsvLibraryUnitTests
{
	TEST_CLASS(TableOutputUnitTests)
	{
	public:
		TEST_METHOD(test1)
		{
			Table table;
			table.getData() = {
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk"}
			};
			std::ostringstream sout;
			sout << table;
			Assert::AreEqual(std::string("123\tabc\r\n456\txyz\r\n789\tmnk"), sout.str());
		}
		TEST_METHOD(test2)
		{
			Table table(';');
			table.getData() = {
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk; pqr; uvw"}
			};
			std::ostringstream sout;
			sout << table;
			Assert::AreEqual(std::string("123;abc\r\n456;xyz\r\n789;\"mnk; pqr; uvw\""), sout.str());
		}
		TEST_METHOD(test3)
		{
			Table table('\t', '\'');
			table.getData() = {
				{"123", "abc", "xyz"},
				{"456"},
				{"789", "mnk, 'pqr', uvw"}
			};
			std::ostringstream sout;
			sout << table;
			Assert::AreEqual(std::string("123\tabc\txyz\r\n456\r\n789\t'mnk, ''pqr'', uvw'"), sout.str());
		}
		TEST_METHOD(test4)
		{
			Table table(',', '\'');
			table.getData() = {
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk, 'pqr', uvw"}
			};
			std::ostringstream sout;
			sout << table;
			Assert::AreEqual(std::string("123,abc\r\n456,xyz\r\n789,'mnk, ''pqr'', uvw'"), sout.str());
		}
		TEST_METHOD(test5)
		{
			Table table(';', '\'', Eol::LF);
			table.getData() = {
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk,\npqr,\nuvw"}
			};
			std::ostringstream sout;
			sout << table;
			Assert::AreEqual(std::string("123;abc\n456;xyz\n789;'mnk,\npqr,\nuvw'"), sout.str());
		}
		TEST_METHOD(test6)
		{
			Table table(';', '"', Eol::CR);
			table.getData() = {
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk;\rpqr;\ruvw"}
			};
			std::ostringstream sout;
			sout << table;
			Assert::AreEqual(std::string("123;abc\r456;xyz\r789;\"mnk;\rpqr;\ruvw\""), sout.str());
		}
		TEST_METHOD(test7)
		{
			Table table('\t', '"', Eol::LF);
			table.getData() = {
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk,\n\"pqr\",\nuvw"}
			};
			std::ostringstream sout;
			sout << table;
			Assert::AreEqual(std::string("123\tabc\n456\txyz\n789\t\"mnk,\n\"\"pqr\"\",\nuvw\""), sout.str());
		}
		TEST_METHOD(test8)
		{
			Table table('\t', '"', Eol::CRLF);
			table.getData() = {
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk\t\"pqr\"\r\nuvw"}
			};
			std::ostringstream sout;
			sout << table;
			Assert::AreEqual(std::string("123\tabc\r\n456\txyz\r\n789\t\"mnk\t\"\"pqr\"\"\r\nuvw\""), sout.str());
		}
		TEST_METHOD(test9)
		{
			Table table(';');
			table.getData() = {
				{"123", "abc"},
				{"456", "xyz"},
				{"789", "mnk;\n\"pqr\";\nuvw"}
			};
			std::ostringstream sout;
			sout << table;
			Assert::AreEqual(std::string("123;abc\r\n456;xyz\r\n789;\"mnk;\n\"\"pqr\"\";\nuvw\""), sout.str());
		}
	};
}
