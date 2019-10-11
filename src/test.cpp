#include <typeinfo>
#include <iomanip>

#include "test.h"

namespace CXXUtility
{

Test::Test(const std::string_view name) :
	_name(name)
{
	this->_startTest();
}

Test::~Test()
{
	this->_endTest();
}

void Test::_startTest()
{
	DebugStream stream;
	
	stream << "+" << std::right << std::setfill('-') << std::setw(79) << "+\n";
	stream << "| " << std::left << std::setfill(' ') << std::setw(76) << this->_name << "|\n";
	stream << "+" << std::right << std::setfill('-') << std::setw(78) << "-+";
}

void Test::_endTest()
{
	DebugStream stream;
	
	stream << "+" << std::right << std::setfill('-') << std::setw(78) << "-+";
}

}
