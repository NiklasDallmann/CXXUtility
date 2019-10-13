#ifndef TEST_H
#define TEST_H

#include <chrono>
#include <exception>
#include <stdint.h>
#include <string_view>
#include <type_traits>
#include <vector>

#include "debugstream.h"

namespace CXXUtility
{

///
/// Base class for Tests
/// 
/// All tests need to derive from this class.
/// 
/// \since	0.2.0
///
class TestSuite
{
public:
	///
	/// Constructs the object using \a name.
	/// 
	/// \since	0.2.0
	///
	TestSuite(const std::string_view name);
	
	///
	/// Destructs the object.
	/// 
	/// \since	0.2.0
	///
	virtual ~TestSuite();
	
	///
	/// Contains and runs all test cases. This method must be reimplemented by deriving types, i.e. all tests.
	/// 
	/// \since	0.2.0
	///
	virtual void operator()() = 0;
	
protected:
	std::string_view _name;
	std::string_view _currentTestName;
	
	void _startTest();
	void _endTest();
};

///
/// Implements a test class \a name that is automatically derives from Test.
/// 
/// \since	0.2.0
///
#define TEST_SUITE(name) \
class name : public CXXUtility::TestSuite \
{ \
public: \
	name() : CXXUtility::TestSuite(#name) \
	{ \
	} \
	virtual void operator()() override; \
}; \
 \
int main() \
{ \
	name()(); \
	return 0; \
} \
 \
void name::operator()()

#define TEST(name) \
this->_currentTestName = #name;


inline DebugStream &success(DebugStream &&debug)
{
	CXX_DEBUG_GLOBAL_IMPL(SUCCESS, green)
}

inline DebugStream &fail(DebugStream &&debug)
{
	CXX_DEBUG_GLOBAL_IMPL(FAIL, red)
}

inline DebugStream &benchmark(DebugStream &&debug)
{
	CXX_DEBUG_GLOBAL_IMPL(BENCHMARK, blue)
}

///
/// Implements a test case with the supplied \a tag. Compares \a actual and \a expected.
/// 
/// If \a actual equals \a expected the test case succeeds; otherwise it fails.
/// 
/// \since	0.2.0
///
template <typename T0, typename T1>
inline void compare(const T0 &actual, const T1 &expected, const std::string_view function, const std::string_view tag)
{
	bool isEqual = actual == expected;
	
	if (isEqual)
	{
		success(DebugStream()) << function << "(\"" << tag << "\")";
	}
	else
	{
		fail(DebugStream()) << function << "(\"" << tag << "\")\n" <<
							   std::setfill(' ') << std::right << std::setw(DebugStream::fillWidth * 2u) << "ACTUAL" <<
							   std::setfill(' ') << std::left << std::setw(DebugStream::fillWidth) << ": " << actual << "\n" <<
							   std::setfill(' ') << std::right << std::setw(DebugStream::fillWidth * 2u) << "EXPECTED" <<
							   std::setfill(' ') << std::left << std::setw(DebugStream::fillWidth) << ": " << expected;
		std::terminate();
	}
}

template <typename Function>
inline void runBenchmark(Function f, const size_t numberOfCycles, const size_t dataSize, const std::string_view function, const std::string_view tag)
{
	auto startTimePoint = std::chrono::high_resolution_clock::now();
	
	for (size_t cycle = 0; cycle < numberOfCycles; cycle++)
	{
		f();
	}
	
	auto endTimePoint = std::chrono::high_resolution_clock::now();
	auto duration = (endTimePoint - startTimePoint);
	double millisecondsTaken = double(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count());
	double millisecondsPerCycle = (millisecondsTaken / double(numberOfCycles));
	double secondsPerCycle = millisecondsPerCycle / double(1000);
	double bandwidth = 0;
	
	bandwidth = (double(dataSize) / double(1000000) / secondsPerCycle);
	
	benchmark(DebugStream()) << function << "(\"" << tag << "\")\n" <<
								std::setfill(' ') << std::right << std::setw(DebugStream::fillWidth * 2u) << "ELAPSED" <<
								std::setfill(' ') << std::left << std::setw(DebugStream::fillWidth) << ": " << millisecondsPerCycle << " ms/cycle\n" <<
								std::setfill(' ') << std::right << std::setw(DebugStream::fillWidth * 2u) << "BANDWIDTH" <<
								std::setfill(' ') << std::left << std::setw(DebugStream::fillWidth) << ": " << bandwidth << " MB/s";
}

#define CXX_COMPARE(actual, expected, tag) \
CXXUtility::compare(actual, expected, this->_currentTestName, tag)

#define CXX_BENCHMARK(f, numberOfCycles, dataSize, tag) \
CXXUtility::runBenchmark(f, numberOfCycles, dataSize, this->_currentTestName, tag)

} // namespace CXXUtility

#endif // TEST_H
