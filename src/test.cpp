#include <typeinfo>
#include <iomanip>

#include "cxxutility/test.h"

namespace CXXUtility
{

TestSuite::TestSuite(const std::string_view name) :
	_name(name)
{
	this->_startTest();
}

TestSuite::~TestSuite()
{
	this->_endTest();
}

void TestSuite::_startTest()
{
	DebugStream stream;

	stream << "+" << std::right << std::setfill('-') << std::setw(79) << "+\n";
	stream << "| " << std::left << std::setfill(' ') << std::setw(76) << this->_name << "|\n";
	stream << "+" << std::right << std::setfill('-') << std::setw(78) << "-+";
}

void TestSuite::_endTest()
{
	DebugStream stream;

	stream << "+" << std::right << std::setfill('-') << std::setw(78) << "-+";
}

}
