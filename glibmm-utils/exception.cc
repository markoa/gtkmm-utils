/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset: 4-*- */

/*Copyright (c) 2005-2006 Dodji Seketeli
 *              2007 Marko Anastasov
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

#include "exception.h"
using namespace std ;

namespace Glib {
namespace Util {

Exception::Exception (const char* a_reason): runtime_error (a_reason)
{}

Exception::Exception (const Glib::ustring &a_reason): runtime_error (a_reason)
{}

Exception::Exception (const Exception &a_other): runtime_error (a_other.what ())
{}

Exception::Exception (const std::exception &a_other):
    runtime_error (a_other.what ())
{}

Exception&
Exception::operator= (const Exception &a_other)
{
    if (this == &a_other) {
        return *this;
    }
    runtime_error::operator= (a_other) ;
    return *this ;
}

Exception::~Exception () throw ()
{}

const char*
Exception::what () const throw ()
{
    return runtime_error::what () ;
}

} // namespace Util

} // namespace Glib

