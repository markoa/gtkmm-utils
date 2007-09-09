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

#include <sys/time.h>
#include <iostream>
#include <map>
#include <list>
#include <vector>
#include <fstream>
#include <tr1/memory>
#include <glibmm.h>
#include <glibmm/thread.h>
#include <glib/gstdio.h>

#include "log-stream.hh"
#include "exception.hh"
#include "date.hh"
#include "ustring.hh"

namespace Glib {
namespace Util {

using namespace std ;

static LogStream::StreamType s_stream_type = LogStream::COUT_STREAM ;
static LogStream::LogLevel s_level_filter = LogStream::LOG_LEVEL_NORMAL ;
static bool s_is_active = true ;

/// the base class of the destination
/// of the messages send to a stream.
/// each log stream uses a particular
/// Log Sink, e.g, a sink that sends messages
/// to stdout, of a sink that sends messages to
/// to a file etc...

class LogSink {
protected:
    mutable Glib::Mutex m_ostream_mutex ;
    ostream *m_out ;

    //non copyable
    LogSink (const LogSink &) ;
    LogSink& operator= (const LogSink &) ;

    LogSink () ;

public:

    LogSink (ostream *a_out) : m_out (a_out) {}

    virtual ~LogSink () {}

    bool bad () const
    {
        Glib::Mutex::Lock lock (m_ostream_mutex) ;
        return m_out->bad () ;
    }

    bool good () const
    {
        Glib::Mutex::Lock lock (m_ostream_mutex) ;
        return m_out->good () ;
    }

    void flush ()
    {
        if (!m_out) throw runtime_error ("underlying ostream not initialized") ;
        Glib::Mutex::Lock lock (m_ostream_mutex) ;
        m_out->flush () ;
    }

    LogSink& write (const char *a_buf, long a_buflen)
    {
        if (!m_out) throw runtime_error ("underlying ostream not initialized") ;
        Glib::Mutex::Lock lock (m_ostream_mutex) ;
        m_out->write (a_buf, a_buflen) ;
        return *this ;
    }

    LogSink& operator<< (const Glib::ustring &a_string)
    {
        if (!m_out) throw runtime_error ("underlying ostream not initialized") ;
        Glib::Mutex::Lock lock (m_ostream_mutex) ;
        *m_out << a_string ;
        return *this ;
    }

    LogSink& operator<< (int an_int)
    {
        if (!m_out) throw runtime_error ("underlying ostream not initialized") ;
        Glib::Mutex::Lock lock (m_ostream_mutex) ;
        *m_out << an_int ;
        return *this ;
    }

    LogSink& operator<< (guint a_guint)
    {
        if (!m_out) throw runtime_error ("underlying ostream not initialized") ;
        Glib::Mutex::Lock lock (m_ostream_mutex) ;
        *m_out << a_guint ;
        return *this ;
    }

    LogSink& operator<< (double a_double)
    {
        if (!m_out) throw runtime_error ("underlying ostream not initialized") ;
        Glib::Mutex::Lock lock (m_ostream_mutex) ;
        *m_out << a_double ;
        return *this ;
    }

    LogSink& operator<< (char a_char)
    {
        if (!m_out) throw runtime_error ("underlying ostream not initialized") ;
        Glib::Mutex::Lock lock (m_ostream_mutex) ;
        *m_out << a_char;
        return *this ;
    }
};//end class LogSink

class CoutLogSink : public LogSink {
public:
    CoutLogSink () : LogSink (&cout) {}
    virtual ~CoutLogSink () {}
};//end class CoutLogSink

class CerrLogSink : public LogSink {
public:
    CerrLogSink () : LogSink (&cerr) {}
    virtual ~CerrLogSink () {}
};//end class OStreamSink

class OfstreamLogSink : public LogSink {
    std::tr1::shared_ptr<ofstream> m_ofstream ;

    void init_from_path (const Glib::ustring &a_file_path)
    {
        Glib::ustring dir (g_path_get_dirname (a_file_path.c_str ())) ;

        if (!Glib::file_test (dir,  Glib::FILE_TEST_IS_DIR)) {
            if (g_mkdir_with_parents (dir.c_str(), S_IRWXU)) {
                throw Exception (Glib::ustring ("failed to create '")
                                 + Glib::ustring (dir + "'")) ;
            }
        }
        m_ofstream.reset (new ofstream (a_file_path.c_str ())) ;
        THROW_IF_FAIL (m_ofstream) ;
        if (!m_ofstream->good ()) {
            THROW ("Could not open file " + a_file_path) ;
        }
        m_out = m_ofstream.get () ;
    }

public:
    OfstreamLogSink (const Glib::ustring &a_file_path) : LogSink (NULL)
    {
        init_from_path (a_file_path);
    }

    OfstreamLogSink () : LogSink (NULL)
    {
        vector<string> path_elems ;
        path_elems.push_back (Glib::get_current_dir ()) ;
        path_elems.push_back (string ("log.txt"));
        init_from_path (Glib::build_filename (path_elems).c_str ()) ;
    }

    virtual ~OfstreamLogSink ()
    {
        if (m_ofstream) {
            m_ofstream->flush ();
            m_ofstream->close ();
            m_ofstream.reset () ;
        }
    }
};//end class OfstreamLogSink

typedef std::tr1::shared_ptr<LogSink> LogSinkSafePtr ;
struct LogStream::Priv
{
    enum LogStream::StreamType stream_type ;
    LogSinkSafePtr sink ;

    //the stack of default domains name
    //to consider when logging functions don't
    //specify the domain name in their parameters
    list<string> default_domains ;

    //the list of domains (keywords) this stream
    //is allowed to log against. (It is a map, just for speed purposes)
    //logging against a domain means "log a message associated with a domain".
    //Logging domains are just keywords associated to the messages that are
    //going to be logged. This helps in for filtering the messages that
    //are to be logged or not.
    map<std::string, bool> allowed_domains ;

    //the log level of this log stream
    enum LogStream::LogLevel level ;

    std::vector<Glib::ustring> enabled_domains_from_env ;

    Priv (const string &a_domain=GLIBMM_GENERAL_DOMAIN) :
            stream_type (LogStream::COUT_STREAM),
            level (LogStream::LOG_LEVEL_NORMAL)
    {
        // Initialize Glib threading.
        // It is a cheap operation as g_thread_supported() is
        // a macro / substitute for a gboolean (g_threads_got_initialized).
        if (! Glib::thread_supported()) Glib::thread_init();

        default_domains.clear () ;
        default_domains.push_front (a_domain) ;

        //GLIBMM_GENERAL_DOMAIN is always enabled by default.
        allowed_domains[GLIBMM_GENERAL_DOMAIN] = true ;
    }

    static Glib::ustring& get_stream_file_path_private ()
    {
        static Glib::ustring s_stream_file_path ;
        if (s_stream_file_path == "") {
            vector<string> path_elems ;
            path_elems.push_back (Glib::get_current_dir ()) ;
            path_elems.push_back (string ("log.txt"));
            s_stream_file_path = Glib::build_filename (path_elems).c_str () ;
        }
        return s_stream_file_path ;
    }

    static Glib::ustring& get_domain_filter_private ()
    {
        static Glib::ustring s_domain_filter ("all") ;
        return s_domain_filter ;
    }

    bool is_logging_allowed (const std::string &a_domain)
    {
        if (!LogStream::is_active ())
            return false ;

        //check domain
        if (allowed_domains.find ("all") == allowed_domains.end ()) {
            if (allowed_domains.find (a_domain) == allowed_domains.end ()) {
                return false ;
            }
        }

        //check log level
        if (level > s_level_filter) {
            return false;
        }
        return true ;
    }

    bool is_logging_allowed ()
    {
        return is_logging_allowed (default_domains.front ()) ;
    }

    void load_enabled_domains_from_env ()
    {
        string str = getenv ("application_log_domains") ;
        if (!str.size()) {
            str = getenv ("APPLICATION_LOG_DOMAINS") ;
        }
        if (!str.size()) {return;}
        Glib::ustring domains_str = Glib::locale_to_utf8 (str.c_str()) ;
        enabled_domains_from_env = Glib::Util::split (domains_str, " ");
    }
}
;//end LogStream::Priv

void
LogStream::set_stream_type (enum StreamType a_type)
{
    s_stream_type = a_type ;
}

enum LogStream::StreamType
LogStream::get_stream_type ()
{
    return s_stream_type ;
}

void
LogStream::set_stream_file_path (const char* a_file_path, long a_len)
{
    Glib::ustring &file_path = LogStream::Priv::get_stream_file_path_private () ;
    file_path.assign (a_file_path, a_len) ;
}

const char*
LogStream::get_stream_file_path ()
{
    return LogStream::Priv::get_stream_file_path_private ().c_str () ;
}

void
LogStream::set_log_level_filter (enum LogLevel a_level)
{
    s_level_filter = a_level ;
}

void
LogStream::set_log_domain_filter (const char* a_domain, long a_len)
{
    Glib::ustring &domain_filter = LogStream::Priv::get_domain_filter_private ();
    domain_filter.assign (a_domain, a_len) ;
}

void
LogStream::activate (bool a_activate)
{
    s_is_active = a_activate ;
}

bool
LogStream::is_active ()
{
    return s_is_active ;
}

LogStream&
LogStream::default_log_stream ()
{
    static LogStream s_default_stream (LOG_LEVEL_NORMAL, GLIBMM_GENERAL_DOMAIN) ;
    return s_default_stream ;
}

LogStream::LogStream (enum LogLevel a_level,
                      const string &a_domain) :
    m_priv (new LogStream::Priv (a_domain))
{

    std::string file_path ;
    if (get_stream_type () == FILE_STREAM) {
        m_priv->sink = LogSinkSafePtr
            (new OfstreamLogSink (get_stream_file_path ())) ;
    } else if (get_stream_type () == COUT_STREAM) {
        m_priv->sink = LogSinkSafePtr (new CoutLogSink) ;
    } else if (get_stream_type () == CERR_STREAM) {
        m_priv->sink = LogSinkSafePtr (new CerrLogSink) ;
    } else {
        g_critical ("LogStream type not supported") ;
        throw Exception ("LogStream type not supported") ;
    }
    m_priv->stream_type = get_stream_type ();
    m_priv->level = a_level ;
    m_priv->load_enabled_domains_from_env () ;

    std::vector<Glib::ustring>::const_iterator d ;
    for (d = m_priv->enabled_domains_from_env.begin ();
         d != m_priv->enabled_domains_from_env.end ();
         ++d) {
        enable_domain (*d) ;
    }
}

LogStream::~LogStream ()
{
    if (!m_priv) throw runtime_error ("double free in LogStrea::~LogStream") ;
    m_priv.reset () ;
}

void
LogStream::enable_domain (const string &a_domain,
                          bool a_do_enable)
{
    if (a_do_enable) {
        m_priv->allowed_domains[a_domain] = true ;
    } else {
        m_priv->allowed_domains.erase (a_domain) ;
    }
}

bool
LogStream::is_domain_enabled (const std::string &a_domain)
{
    if (m_priv->allowed_domains.find (a_domain)
        != m_priv->allowed_domains.end ()) {
        return true ;
    }
    return false ;
}

LogStream&
LogStream::write (const char* a_buf, long a_buflen, const string &a_domain)
{
    if (!m_priv->is_logging_allowed (a_domain))
        return *this ;

    long len = 0 ;
    if (a_buflen > 0) {
        len = a_buflen ;
    } else {
        if (!a_buf)
            len = 0 ;
        else
            len = strlen (a_buf) ;
    }
    m_priv->sink->write (a_buf, len) ;
    if (m_priv->sink->bad ()) {
        cerr << "write failed\n" ;
        throw Exception ("write failed") ;
    }
    return *this ;
}

LogStream&
LogStream::write (int a_msg, const string &a_domain)
{
    if (!m_priv || !m_priv->sink)
        return *this ;

    if (!m_priv->is_logging_allowed (a_domain))
        return *this ;

    *m_priv->sink << a_msg;
    if (m_priv->sink->bad ()) {
        cout << "write failed" ;
        throw Exception ("write failed") ;
    }
    return *this ;
}

LogStream&
LogStream::write (guint a_msg, const string &a_domain)
{
    if (!m_priv || !m_priv->sink)
        return *this ;

    if (!m_priv->is_logging_allowed (a_domain))
        return *this ;

    *m_priv->sink << a_msg;
    if (m_priv->sink->bad ()) {
        cout << "write failed" ;
        throw Exception ("write failed") ;
    }
    return *this ;
}

LogStream&
LogStream::write (double a_msg,
                  const string &a_domain)
{
    if (!m_priv || !m_priv->sink)
        return *this ;

    if (!m_priv->is_logging_allowed (a_domain))
        return *this ;

    *m_priv->sink << a_msg;
    if (m_priv->sink->bad ()) {
        cout << "write failed" ;
        throw Exception ("write failed") ;
    }
    return *this ;
}

LogStream&
LogStream::write (char a_msg,
                  const string &a_domain)
{
    if (!m_priv || !m_priv->sink)
        return *this ;

    if (!m_priv->is_logging_allowed (a_domain))
        return *this ;

    *m_priv->sink << a_msg;
    if (m_priv->sink->bad ()) {
        cout << "write failed" ;
        throw Exception ("write failed") ;
    }
    return *this ;
}

void
LogStream::push_domain (const string &a_domain)
{
    m_priv->default_domains.push_front (a_domain) ;
}

void
LogStream::pop_domain ()
{
    if (m_priv->default_domains.size () <= 1) {
        return ;
    }
    m_priv->default_domains.pop_front () ;
}

LogStream&
LogStream::write (const Glib::ustring &a_msg, const string &a_domain)
{
    return write (a_msg.c_str (), a_msg.bytes (), a_domain) ;
}


LogStream&
LogStream::operator<< (const Glib::ustring &a_string)
{
    return write (a_string, m_priv->default_domains.front ()) ;
}

LogStream&
LogStream::operator<< (int a_msg)
{
    return write (a_msg, m_priv->default_domains.front ()) ;
}

LogStream&
LogStream::operator<< (guint a_msg)
{
    return write (a_msg, m_priv->default_domains.front ()) ;
}

LogStream&
LogStream::operator<< (double a_msg)
{
    return write (a_msg, m_priv->default_domains.front ()) ;
}

LogStream&
LogStream::operator<< (char a_msg)
{
    return write (a_msg, m_priv->default_domains.front ()) ;

}

LogStream&
LogStream::operator<< (LogStream& (*a_manipulator) (LogStream &))
{
    a_manipulator (*this) ;
    return *this ;
}

LogStream&
timestamp (LogStream &a_stream)
{
    if (!a_stream.m_priv->is_logging_allowed ())
        return a_stream ;
    Glib::ustring now_str ;
    get_current_datetime (now_str) ;
    a_stream << now_str ;
    return a_stream ;
}

LogStream&
flush (LogStream &a_stream)
{
    if (!a_stream.m_priv->is_logging_allowed ())
        return a_stream ;

    a_stream.m_priv->sink->flush () ;
    return a_stream ;
}

LogStream&
endl (LogStream &a_stream)
{
    if (!a_stream.m_priv->is_logging_allowed ())
        return a_stream ;

    a_stream  << '\n' ;
    a_stream << flush  ;
    return a_stream ;
}

LogStream&
level_normal (LogStream &a_stream)
{
    a_stream.m_priv->level = LogStream::LOG_LEVEL_NORMAL ;
    return a_stream ;
}

LogStream&
level_verbose (LogStream &a_stream)
{
    a_stream.m_priv->level = LogStream::LOG_LEVEL_VERBOSE;
    return a_stream ;
}

} // namespace Util
} // namespace Glib

