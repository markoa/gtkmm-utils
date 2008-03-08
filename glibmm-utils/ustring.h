/* -*- Mode: C++; indent-tabs-mode: nil; c-basic-offset: 4 -*- */

/* Copyright (C) 2005-2006 Dodji Seketeli
 *               2007 Marko Anastasov
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public License
 * along with this library; if not, write to the
 * Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef __GLIBMM_USTRING_UTILS_H__
#define __GLIBMM_USTRING_UTILS_H__

#include <sstream>
#include <typeinfo>
#include <vector>
#include <glibmm/ustring.h>
#include "exception.h"

namespace Glib {

namespace Util {

/// \brief Conversion exception.
class BadConversion : public Exception
{
public:
    BadConversion(const Glib::ustring& msg) : Exception(msg) {}
};

/// \brief Splits a string into tokens.
std::vector<Glib::ustring> split(const Glib::ustring& str,
                                 const Glib::ustring& delim);

/// \brief Splits a string by whitespace (after skipping any leading
/// whitespace) - like Perl's split function without the pattern.
std::vector<Glib::ustring> split(const Glib::ustring& str);

/// \brief Trims left hand side whitespace
void                       trim_left(Glib::ustring& str);

/// \brief Trims right hand side whitespace
void                       trim_right(Glib::ustring& str);

/// \brief Trims any whitespace from the string
void                       trim(Glib::ustring& str);

/// \brief Converts an ostream-able type to a Glib::ustring
template<typename T>
inline Glib::ustring stringify(const T& x)
{
    std::ostringstream os;

    if (! (os << x))
        throw BadConversion(
            "Cannot convert " + Glib::ustring(typeid(x).name()) + " to string");

    return os.str();
}

/// \brief Converts a string to an arbitrary type that supports iostream.
/// Inspired by the C++ FAQ.
/// \param str  the string to convert
/// \param x  the object to hold converted value
/// \param fail_if_leftover_chars  if set to true, the function will
/// throw a BadConversion exception if any characters are remaining after
/// the conversion
template<typename T>
inline void convert_to(const Glib::ustring& str,
                       T& x,
                       bool fail_if_leftover_chars = true)
{
    std::istringstream is(str.raw());
    char c;

    if ((! (is >> x)) || (fail_if_leftover_chars && is.get(c)))
        throw BadConversion(str);
}

/// \brief Converts a string to an arbitrary type that supports iostream
/// by returning by value.
/// This is a convenience function which is handy for conversions to
/// primitive types.
/// \param str  the string to convert
/// \param fail_if_leftover_chars  if set to true, the function will
/// throw a BadConversion exception if any characters are remaining after
/// the conversion
/// \return  the object with converted value
template<typename T>
inline T convert_to(const Glib::ustring& str,
                    bool fail_if_leftover_chars = true)
{
    T x;
    convert_to(str, x, fail_if_leftover_chars);
    return x;
}

/// \brief a printf() that returns a Glib::ustring
Glib::ustring uprintf(const Glib::ustring& format, ...);

} // namespace Util

} // namespace Glib

#endif // __GLIBMM_USTRING_UTILS_H__
