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

#ifndef __GLIBMM_UTILS_EXCEPTION_H__
#define __GLIBMM_UTILS_EXCEPTION_H__

#include <stdexcept>
#include <glibmm/ustring.h>
#include "log-stream-utils.hh"

namespace Glib {
namespace Util {

class Exception: public std::runtime_error
{
public:
    Exception (const char* a_reason) ;
    Exception (const Glib::ustring &a_reason) ;
    Exception (const Exception &a_other) ;
    Exception (const std::exception &) ;
    Exception& operator= (const Exception &a_other) ;
    virtual ~Exception () throw ();
    const char* what () const throw ();
};//class Exception

#define THROW_IF_FAIL(a_cond) \
if (!(a_cond)) { \
LOG_EXCEPTION ("condition (" << #a_cond << ") failed; raising exception\n" ) ;\
throw Glib::Util::Exception                                                 \
    (Glib::ustring ("Assertion failed: ") + #a_cond)  ;\
}

#define THROW_IF_FAIL2(a_cond, a_reason) \
if (!(a_cond)) { \
LOG_EXCEPTION ("condition (" << #a_cond << ") failed; raising exception " << a_reason <<"\n");\
throw Glib::Util::Exception (a_reason)  ;\
}

#define THROW_IF_FAIL3(a_cond, type, a_reason) \
if (!(a_cond)) { \
LOG_EXCEPTION ("condition (" << #a_cond << ") failed; raising exception " << #type << \
<< ":  " << a_reason << "\n" ) ; throw type (a_reason)  ;\
}

#define THROW(a_reason) \
LOG_EXCEPTION ("raised exception: "<< (Glib::ustring (a_reason)) << "\n"); \
throw Glib::Util::Exception (Glib::ustring (a_reason))  ;

#define THROW_EMPTY \
LOG_EXCEPTION ("raised empty exception " << endl) ; \
throw ;

#define THROW_EXCEPTION(type, message) \
LOG_EXCEPTION ("raised " << #type << ": "<< message<< "\n") ; \
throw type (message) ;

#define TRACE_EXCEPTION(exception) \
LOG_EXCEPTION ("catched exception: " << exception.what () << "\n")

#define RETHROW_EXCEPTION(exception) \
LOG_EXCEPTION ("catched and rethrowing exception: " << exception.what() << "\n")

#define RETURN_VAL_IF_FAIL(expression, value) \
if (!(expression)) { \
LOG_ERROR ("assertion " << #expression << " failed. Returning " << #value << "\n") ; \
return value ; \
}

#define RETURN_IF_FAIL(expression) \
if (!(expression)) { \
LOG_ERROR ("assertion " << #expression << " failed. Returning.\n") ; \
return ; \
}

#ifndef GLIBMM_TRY
#define GLIBMM_TRY try {
#endif

#ifndef GLIBMM_CATCH_NOX
#define GLIBMM_CATCH_NOX \
} catch (Glib::Exception &e) { \
    LOG_ERROR (e.what ()) ; \
} catch (std::exception &e) { \
    LOG_ERROR (e.what ()) ; \
} catch (...) { \
    LOG_ERROR ("An unknown error occured") ; \
}
#endif

#ifndef GLIBMM_CATCH_AND_RETURN_NOX
#define GLIBMM_CATCH_AND_RETURN_NOX(a_value) \
} catch (Glib::Exception &e) { \
    LOG_ERROR (e.what ()) ; \
    return a_value ; \
} catch (std::exception &e) { \
    LOG_ERROR (e.what ()) ; \
    return a_value ; \
} catch (...) { \
    LOG_ERROR ("An unknown error occured") ; \
    return a_value ; \
}
#endif

} // namespace Util
} // namespace Glib 

#endif //__GLIBMM_UTILS_EXCEPTION_H__
