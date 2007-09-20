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

#include <glibmm.h>
#include "exception.hh"
#include "scope-logger.hh"

namespace Glib {
namespace Util {

struct ScopeLoggerPriv
{
    Glib::Timer timer ;
    LogStream *out ;
    bool can_free ;
    Glib::ustring name ;
    Glib::ustring domain ;

    ScopeLoggerPriv (const char*a_scope_name,
                     enum LogStream::LogLevel a_level,
                     const Glib::ustring& a_log_domain,
                     bool a_use_default_log_stream) :
        out (NULL), can_free (false)
    {
        if (!a_use_default_log_stream) {
            out = new LogStream (a_level);
            can_free = true ;
        } else {
            out = &(LogStream::default_log_stream ()) ;
            can_free = false ;
        }
        name = a_scope_name ;
        domain = a_log_domain ;

        out->push_domain (a_log_domain) ;
        *out  << "|{|" << name << ":{\n" ;
        out->pop_domain () ;

        timer.start () ;
        out = out ;
    }

    ~ScopeLoggerPriv ()
    {
        timer.stop () ;

        if (!out) {return;}

        out->push_domain (domain) ;
        *out << "|}|" << name <<":}elapsed: " << timer.elapsed () << "secs \n" ;
        out->pop_domain () ;
        if (can_free) {
            if (out) {
                delete out ;
            }
        }
        out = NULL ;
    }
};


ScopeLogger::ScopeLogger (const char*a_scope_name,
                          enum LogStream::LogLevel a_level,
                          const Glib::ustring& a_log_domain,
                          bool a_use_default_log_stream) :
    m_priv (new ScopeLoggerPriv (a_scope_name, a_level,
                                 a_log_domain, a_use_default_log_stream))
{
}

ScopeLogger::~ScopeLogger ()
{
    //LOG_DD ("delete") ;
}

} // namespace Util
} // namespace Glib
