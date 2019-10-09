#ifndef DEBUGSTREAM_H
#define DEBUGSTREAM_H

#include <iostream>
#include <sstream>
#include <string>

namespace CXXUtility
{

class DebugStream
{
public:
	static const std::string standard;
	static const std::string red;
	static const std::string blue;
	static const std::string yellow;
	static const std::string green;
	static const std::string magenta;
	static const std::string cyan;
	
	DebugStream();
	~DebugStream();
	
	template <typename T>
	DebugStream &insert(const T &t)
	{
		this->_stream << t;
		return *this;
	}
	
private:
	std::stringstream _stream;
};

template <typename T>
DebugStream &operator<<(DebugStream &&debug, const T &t)
{
	return debug.insert(t);
}

template <typename T>
DebugStream &operator<<(DebugStream &debug, const T &t)
{
	return debug.insert(t);
}

} // namespace CXXUtility

#define debugLog		CXXUtility::DebugStream() << "DEBUG	"
#define warningLog		CXXUtility::DebugStream() << CXXUtility::DebugStream::yellow << "WARN	" << CXXUtility::DebugStream::standard
#define errorLog		CXXUtility::DebugStream() << CXXUtility::DebugStream::red << "ERROR	" << CXXUtility::DebugStream::standard
#define traceLog		CXXUtility::DebugStream() << CXXUtility::DebugStream::magenta << "TRACE	" << CXXUtility::DebugStream::standard
#define infoLog			CXXUtility::DebugStream() << CXXUtility::DebugStream::cyan << "INFO	" << CXXUtility::DebugStream::standard

#endif // DEBUGSTREAM_H
