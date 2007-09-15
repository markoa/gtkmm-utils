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

#ifndef __GLIBMM_UTILS_LOG_STREAM_H__
#define __GLIBMM_UTILS_LOG_STREAM_H__

#include <string>
#include <tr1/memory>
#include <glibmm/ustring.h>

#ifndef GLIBMM_DEFAULT_DOMAIN
#define GLIBMM_DEFAULT_DOMAIN __FILE__
#endif

#ifndef GLIBMM_GENERAL_DOMAIN
#define GLIBMM_GENERAL_DOMAIN "general-domain"
#endif

using std::string ;
namespace Glib {
namespace Util {

/// \brief The log stream class.
/// It features logging to cout, cerr and files.
/// It also features log domains and log levels.
class LogStream
{
    friend LogStream& timestamp (LogStream &);
    friend LogStream& flush (LogStream &) ;
    friend LogStream& endl (LogStream &) ;
    struct Priv ;
    std::tr1::shared_ptr<Priv> m_priv ;

    //forbid copy/assignation
    LogStream (LogStream const&) ;
    LogStream& operator= (LogStream const&) ;

protected:

public:

    enum StreamType {
        FILE_STREAM = 1,
        COUT_STREAM = 1 >> 1,
        CERR_STREAM = 1 >> 2,
        RFU0,//reserved for future usage
        RFU1,
        RFU2
    };

    enum LogLevel {
        LOG_LEVEL_NORMAL=0,
        LOG_LEVEL_VERBOSE
    };

    /// \brief set the type of all the log streams that will be instanciated
    ///(either cout, cerr, or log file). By default, the type of stream is
    /// set to COUT_STREAM. All the logs are sent to stdout.
    /// \param a_type the type of the log stream
    static void set_stream_type (enum StreamType a_type) ;

    /// \brief gets the type of the instances of #LogStream
    /// \return the stream type as set by LogStream::set_stream_type().
    static enum StreamType get_stream_type () ;

    /// in the case where the stream type is set to FILE_STREAM,
    /// this methods sets the path of the file to log into. By default,
    /// the log file is ./log.txt
    /// \param a_file_path the log file path.
    /// \param a_len the length of the file_path. If <0, it means that a_file_path
    /// is a zero terminated string.
    static void set_stream_file_path (const char* a_file_path, long a_len=-1) ;

    /// \brief gets the log file path, in case the stream type is set to
    /// FILE_STREAM
    /// \return the path to the log file.
    static const char* get_stream_file_path () ;

    /// \brief sets the log level filter.
    /// if the filter is set to LOG_LEVEL_NORMAL, only the log streams that
    /// have a log level set to LOG_LEVEL_NORMAL will actually log data.
    /// If the filter is set to LOG_LEVEL_VERBOSE, streams set to
    /// LOG_LEVEL_NORMAL *and* streams set to LOG_LEVEL_VERBOSE will be
    /// logging data.
    ///
    /// \param a_level the level of verbosity you want your log streams to have.
    static void set_log_level_filter (enum LogLevel a_level) ;

    /// \brief sets a filter on the log domain
    /// only streams that have the same domain as the one set here will
    /// be logging data.
    /// \param a_domain the domain name.
    /// \a_len the length of the domain name. If <0, it means that a_domain
    /// is a zero terminated string.
    static void set_log_domain_filter (const char* a_domain, long a_len=-1) ;

    /// \brief activate/de-activate the logging.
    /// \param a_activate true to activate the logging, false to deactivate.
    static void activate (bool a_activate) ;

    /// \brief tests wether the logging is activated or not.
    /// \return true if the logging is activated, false otherwise.
    static bool is_active () ;

    /// \brief gets the log stream instanciated by the system by default.
    /// the options of this log stream are the global options set before
    /// the first call to this method.
    /// \return the log stream instanciated by default.
    static LogStream& default_log_stream () ;


    /// \brief default constructor of a log stream
    /// \param a_level the log level of the stream. This stream
    /// will log data if its log level is inferior or equal to
    /// the log level filter defined by LogStream::set_log_level_filter().
    /// \param a_domain the log domain. A stream will log data if its
    /// its log level is <= to the log level filter, *and* if its domain equals
    /// the domain filter.
    LogStream (enum LogLevel a_level=LOG_LEVEL_NORMAL,
               const string &a_default_domain=GLIBMM_GENERAL_DOMAIN) ;

    /// \brief destructor of the log stream class
    virtual ~LogStream () ;

    /// \brief enable or disable logging for a domain
    /// \param a_domain the domain to enable logging for
    /// \param a_do_enable when set to true, enables the logging for domain
    /// @a_domain, disable it otherwise.
    void enable_domain (const string &a_domain,
                        bool a_do_enable=true) ;

    /// \return true is logging is enabled for domain @a_domain
    bool is_domain_enabled (const string &a_domain) ;

    /// \brief writes a text string to the stream
    /// \param a_buf the buffer that contains the text string.
    /// \param a_buflen the length of the buffer. If <0, a_buf is
    /// considered as a zero terminated string.
    /// \param a_domain the domain the string has to be logged against.
    LogStream& write (const char *a_buf,
                      long a_buflen =-1,
                      const string &a_domain=GLIBMM_GENERAL_DOMAIN) ;

    /// \brief log a message to the stream
    /// \param a_msg the message to log
    /// \param a_domain the domain to log against
    LogStream& write (const Glib::ustring &a_msg,
                      const string &a_domain=GLIBMM_GENERAL_DOMAIN) ;

    LogStream& write (int a_msg,
                      const string &a_domain=GLIBMM_GENERAL_DOMAIN) ;

    LogStream& write (guint a_msg,
                      const string &a_domain=GLIBMM_GENERAL_DOMAIN) ;

    LogStream& write (double a_msg,
                      const string &a_domain=GLIBMM_GENERAL_DOMAIN) ;

    LogStream& write (char a_msg,
                      const string &a_domain=GLIBMM_GENERAL_DOMAIN) ;

    /// set the domain in against which all the coming
    /// messages will be logged.
    /// This is to be used in association with the << operators where
    /// we cannot specify the domain to log against, unlike LogStream::write() .
    /// \param a_domain the domain to log against.
    void push_domain (const string &a_domain) ;

    /// pops the last domain that has been pushed using LogStream::push_domain.
    void pop_domain () ;

    /// \brief log zero teriminated strings
    /// \param a_string the string to log
    LogStream& operator<< (const Glib::ustring &a_string) ;

    /// \brief log an integer
    /// \param an_int the integer to log
    LogStream& operator<< (int an_int) ;
    
    /// \brief log a guint
    /// \param a_guint the guint to log
    LogStream& operator<< (guint an_int) ;

    /// \brief log a double
    /// \param the double to log
    LogStream& operator<< (double a_double) ;

    /// \brief log a character
    /// \param a_char the char to log
    LogStream& operator<< (char a_char) ;

    /// \brief  log a stream manipulator
    /// \param a_manipulator the LogStream manipulator to log
    LogStream& operator<< (LogStream& (*a_manipulator) (LogStream&)) ;

    friend LogStream& level_normal (LogStream &a_stream) ;

    friend LogStream& level_verbose (LogStream &a_stream) ;

};//end class LogStream

/// \brief logs a timestamp. Basically the
/// the current date. You use it like:
/// Glib::Util::LogStream out ; out << Glib::Util::timestamp ;
LogStream& timestamp (LogStream&);

/// \brief flushes the stream
/// Use it like: Glib::Util::LogStream out ;
/// out << "Hello" << Glib::Util::flush ;
LogStream& flush (LogStream &) ;

/// \brief log a '\\n' and flushes the stream
/// Use it like: Glib::Util::LogStream out ;
/// out << "hello"<< Glib::Util::endl ;
LogStream& endl (LogStream &) ;

/// \brief sets the log level to normal
/// Use it like Glib::Util::LogStream out ;
/// out << Glib::Util::level_normal << "blabla" ;
LogStream& level_normal (LogStream &) ;

/// \brief sets the log level to verbose
/// Use it lik: Glib::Util::LogStream out ;
/// out << Glib::Util::level_verbose << "bla bla bla" ;
LogStream& level_verbose (LogStream &) ;

} // namespace Util
} // namespace Glib

#endif //__GLIBMM_UTILS_LOG_STREAM_H__
