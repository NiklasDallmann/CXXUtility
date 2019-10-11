#ifndef SFINAE_H
#define SFINAE_H

#include <sstream>
#include <type_traits>

namespace CXXUtility
{

template <typename T, typename = void>
struct is_sstream_compatible : std::false_type
{
};

template <typename T>
struct is_sstream_compatible<T, std::void_t<decltype (std::declval<std::stringstream>() << std::declval<T>())>> : std::true_type
{
};

}

#endif // SFINAE_H
