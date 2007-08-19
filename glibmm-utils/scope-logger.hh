/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

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

#ifndef __GLIBMM_UTILS_SCOPE_LOGGER_H__
#define __GLIBMM_UTILS_SCOPE_LOGGER_H__

#include <tr1/memory>
#include "log-stream-utils.hh"

namespace Glib {
namespace Util {

struct ScopeLoggerPriv ;
class ScopeLogger
{
    friend struct ScopeLoggerPriv ;

    std::tr1::shared_ptr<ScopeLoggerPriv> m_priv ;
    //forbid copy/assignation
    ScopeLogger (ScopeLogger const &) ;
    ScopeLogger& operator= (ScopeLogger const &) ;
    ScopeLogger () ;

public:

    ScopeLogger (const char*a_scope_name,
                 enum LogStream::LogLevel a_level=LogStream::LOG_LEVEL_NORMAL,
                 const Glib::ustring &a_log_domain="general",
                 bool a_use_default_log_stream=true) ;

    virtual ~ScopeLogger () ;

};//class ScopeLogger

} // namespace Util
} // namespace Glib

#endif // __GLIBMM_UTILS_SCOPE_LOGGER_H__
