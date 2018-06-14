#ifndef _STRINGHELPER_HPP
#define _STRINGHELPER_HPP

#include <sstream>

// Since std::to_string doesn't work on MinGW we have to implement
// our own to support all platforms.
template <typename T>
std::string toString(const T& value);

#include "stringHelper.inl"
#endif // BOOK_STRINGHELPER_HPP