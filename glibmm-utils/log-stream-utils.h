/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset: 4-*- */

/* Copyright (c) 2005-2006 Dodji Seketeli
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

#ifndef __GLIBMM_UTILS_LOG_STREAM_UTILS_H__
#define __GLIBMM_UTILS_LOG_STREAM_UTILS_H__

#include <cassert>
#include <cstdlib>
#include "log-stream.h"
#include "scope-logger.h"

#ifndef HERE
#define HERE __ASSERT_FUNCTION << ":" <<__FILE__<< ":" << __LINE__ << ":"
#endif

#ifndef PRETY_FUNCTION_NAME_
#define PRETTY_FUNCTION_NAME_ __ASSERT_FUNCTION
#endif

#ifndef LOG_STREAM
#define LOG_STREAM Glib::Util::LogStream::default_log_stream ()
#endif

#ifndef LOG_MARKER_INFO
#define LOG_MARKER_INFO "|I|"
#endif

#ifndef LOG_MARKER_ERROR
#define LOG_MARKER_ERROR "|E|"
#endif

#ifndef LOG_MARKER_EXCEPTION
#define LOG_MARKER_EXCEPTION "|X|"
#endif

#ifndef LOG_LEVEL_NORMAL___
#define LOG_LEVEL_NORMAL___ Glib::Util::level_normal
#endif

#ifndef LOG_LEVEL_VERBOSE___
#define LOG_LEVEL_VERBOSE___ Glib::Util::level_verbose
#endif

#ifndef LOG
#define LOG(message) \
LOG_STREAM << LOG_LEVEL_NORMAL___ << LOG_MARKER_INFO << HERE << message << Glib::Util::endl
#endif

#ifndef LOG_D
#define LOG_D(message, domain) \
LOG_STREAM.push_domain (domain) ; LOG (message) ; LOG_STREAM.pop_domain ();
#endif

#ifndef LOG_DD
#define LOG_DD(message) LOG_D(message, GLIBMM_DEFAULT_DOMAIN)
#endif

#ifndef LOG_ERROR
#define LOG_ERROR(message) \
LOG_STREAM << LOG_LEVEL_NORMAL___ << LOG_MARKER_ERROR << HERE << message << Glib::Util::endl
#endif

#ifndef LOG_EXCEPTION
#define LOG_EXCEPTION(message) \
LOG_STREAM << LOG_LEVEL_NORMAL___ << LOG_MARKER_EXCEPTION << HERE << message << Glib::Util::endl
#endif

#ifndef LOG_EXCEPTION_D
#define LOG_EXCEPTION_D(message, domain) \
LOG_STREAM.push_domain (domain) ; LOG_EXCEPTION (message) ; LOG_STREAM.pop_domain() ;
#endif

#ifndef LOG_EXCEPTION_DD
#define LOG_EXCEPTION_DD(message) LOG_EXCEPTION_D (message, GLIBMM_DEFAULT_DOMAIN)
#endif

#ifndef LOG_ERROR_D
#define LOG_ERROR_D(message, domain) \
LOG_STREAM.push_domain (domain) ; LOG_ERROR (message) ; LOG_STREAM.pop_domain() ;
#endif

#ifndef LOG_ERROR_DD
#define LOG_ERROR_DD(message) LOG_ERROR_D (message, GLIBMM_DEFAULT_DOMAIN)
#endif

#ifndef LOG_VERBOSE
#define LOG_VERBOSE(message) \
LOG_STREAM << LOG_LEVEL_VERBOSE___ << LOG_MARKER_INFO << HERE << message << Glib::Util::endl
#endif

#ifndef LOG_VERBOSE_D
#define LOG_VERBOSE_D(message) \
LOG_STREAM.push_domain (domain) ; LOG_VERBOSE(message) ;LOG_STREAM.pop_domain();
#endif

#ifndef LOG_SCOPE
#define LOG_SCOPE(scopename) \
Glib::Util::ScopeLogger scope_logger (scopename, Glib::Util::LogStream::LOG_LEVEL_VERBOSE) ;
#endif

#ifndef LOG_SCOPE_D
#define LOG_SCOPE_D(scopename, domain) \
Glib::Util::ScopeLogger scope_logger \
        (scopename, Glib::Util::LogStream::LOG_LEVEL_VERBOSE, domain) ;
#endif

#ifndef LOG_SCOPE_NORMAL
#define LOG_SCOPE_NORMAL(scopename) \
Glib::Util::ScopeLogger scope_logger (scopename, Glib::Util::LogStream::LOG_LEVEL_NORMAL) ;
#endif

#ifndef LOG_SCOPE_NORMAL_D
#define LOG_SCOPE_NORMAL_D(scopename, domain) \
Glib::Util::ScopeLogger scope_logger \
    (scopename, Glib::Util::LogStream::LOG_LEVEL_NORMAL, domain) ;
#endif

#ifndef LOG_FUNCTION_SCOPE
#define LOG_FUNCTION_SCOPE LOG_SCOPE(PRETTY_FUNCTION_NAME_)
#endif

#ifndef LOG_FUNCTION_SCOPE_D
#define LOG_FUNCTION_SCOPE_D(domain) LOG_SCOPE_D(PRETTY_FUNCTION_NAME_, domain)
#endif

#ifndef LOG_FUNCTION_SCOPE_NORMAL
#define LOG_FUNCTION_SCOPE_NORMAL LOG_SCOPE_NORMAL(PRETTY_FUNCTION_NAME_)
#endif

#ifndef LOG_FUNCTION_SCOPE_NORMAL_D
#define LOG_FUNCTION_SCOPE_NORMAL_D(domain) \
    LOG_SCOPE_NORMAL_D(PRETTY_FUNCTION_NAME_, domain)
#endif

#ifndef LOG_FUNCTION_SCOPE_NORMAL_DD
#define LOG_FUNCTION_SCOPE_NORMAL_DD LOG_FUNCTION_SCOPE_NORMAL_D(GLIBMM_DEFAULT_DOMAIN)
#endif

#endif // __GLIBMM_UTILS_LOG_STREAM_UTILS_H__
