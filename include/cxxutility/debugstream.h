#ifndef DEBUGSTREAM_H
#define DEBUGSTREAM_H

#include <iomanip>
#include <iostream>
#include <sstream>
#include <stddef.h>
#include <string>

#include "cxxutility/definitions.h"
#include "cxxutility/sfinae.h"

#if defined(CXX_GCC) || defined(CXX_CLANG)
#include <cxxabi.h>
#endif

///
/// Top level namespace for the CXXUtility library.
///
/// \since	0.1.0
///
namespace CXXUtility
{

///
/// Implements a thread-safe debug stream.
///
/// This implementation is compatible with all types that implement `operator<<` for `std::stringstream`.
///
/// \since	0.1.0
///
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

	static constexpr uint32_t fillWidth = 10u;

	///
	/// Constructs a DebugStream. The constructed object may immediately used to print output.
	///
	/// \since	0.1.0
	///
	DebugStream();

	///
	/// Destructs the object and prints the content to `std::cout`.
	///
	/// \since	0.1.0
	///
	~DebugStream();

	///
	/// Appends \a t to the internal buffer.
	///
	/// \since	0.1.0
	///
	template <typename T>
	DebugStream &insert(const T &t)
	{
		if constexpr (is_sstream_compatible<T>::value)
		{
			this->_stream << t;
		}
		else
		{
			this->_stream << this->_typeName<T>() << "()";
		}

		return *this;
	}

private:
	std::stringstream _stream;

	template <typename T>
	std::string _typeName()
	{
		std::string returnValue;

#if defined(CXX_GCC) || defined(CXX_CLANG)
		size_t length = 0;
		int status = 0;
		char *name = abi::__cxa_demangle(typeid(T).name(), nullptr, &length, &status);

		returnValue = std::string(name, length);

		free(name);
#else
		returnValue = typeid(T).name();
#endif

		return returnValue;
	}
};

///
/// Inserts \a t into \a debug.
///
/// \since	0.1.0
///
template <typename T>
DebugStream &operator<<(DebugStream &&debug, const T &t)
{
	return debug.insert(t);
}

///
/// \overload	template <typename T> DebugStream &operator<<(DebugStream &&debug, const T &t)
/// \since		0.1.0
///
template <typename T>
DebugStream &operator<<(DebugStream &debug, const T &t)
{
	return debug.insert(t);
}

#define CXX_DEBUG_GLOBAL_IMPL(name, color) \
debug << DebugStream::color << std::setfill(' ') << std::left << std::setw(DebugStream::fillWidth) << #name << DebugStream::standard << ": "; \
return debug;

inline DebugStream &debug(DebugStream &&debug)
{
	CXX_DEBUG_GLOBAL_IMPL(DEBUG, standard)
}

inline DebugStream &warning(DebugStream &&debug)
{
	CXX_DEBUG_GLOBAL_IMPL(WARNING, yellow)
}

inline DebugStream &error(DebugStream &&debug)
{
	CXX_DEBUG_GLOBAL_IMPL(ERROR, red)
}

inline DebugStream &trace(DebugStream &&debug)
{
	CXX_DEBUG_GLOBAL_IMPL(TRACE, magenta)
}

inline DebugStream &info(DebugStream &&debug)
{
	CXX_DEBUG_GLOBAL_IMPL(INFO, cyan)
}

} // namespace CXXUtility

#define cxxdebug \
CXXUtility::debug(CXXUtility::DebugStream())

#define cxxwarning \
CXXUtility::warning(CXXUtility::DebugStream())

#define cxxerror \
CXXUtility::error(CXXUtility::DebugStream())

#define cxxtrace \
CXXUtility::trace(CXXUtility::DebugStream())

#define cxxinfo \
CXXUtility::info(CXXUtility::DebugStream())

#endif // DEBUGSTREAM_H
