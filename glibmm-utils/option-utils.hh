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

#ifndef __GLIBMM_UTILS_OPTION_UTILS_H__
#define __GLIBMM_UTILS_OPTION_UTILS_H__

#include <glibmm.h>

namespace Glib {
namespace Util {

class OptionDesc {
    Glib::ustring m_long_name ;
    gchar m_short_name ;
    Glib::ustring m_description ;
    Glib::ustring m_arg_description ;
    enum Glib::OptionEntry::Flags m_flags ;

public:
    OptionDesc () :
        m_short_name (0),
        m_flags ((Glib::OptionEntry::Flags)0)
    {}

    OptionDesc (const Glib::ustring& a_long_name,
                const gchar a_short_name,
                const Glib::ustring& a_description,
                const Glib::ustring& a_arg_description,
                const Glib::OptionEntry::Flags a_flags) :
        m_long_name (a_long_name),
        m_short_name (a_short_name),
        m_description (a_description),
        m_arg_description (a_arg_description),
        m_flags (a_flags)
    {}

    const Glib::ustring& long_name () {return m_long_name;}
    void long_name (const Glib::ustring& a_in) {m_long_name = a_in;}

    gchar short_name () {return m_short_name;}
    void short_name (gchar a_in) {m_short_name = a_in;}

    const Glib::ustring& description () {return m_description;}
    void description (const Glib::ustring& a_in) {m_description = a_in;}

    const Glib::ustring& arg_description () {return m_arg_description;}
    void arg_description (const Glib::ustring& a_in) {m_arg_description = a_in;}

    Glib::OptionEntry::Flags flags () {return m_flags;}
    void flags (Glib::OptionEntry::Flags a_in) {m_flags = a_in;}
}; //end class OptionDesc

void option_desc_to_option (OptionDesc &a_desc,
                            Glib::OptionEntry &a_option) ;

void append_options_to_group (OptionDesc *a_descs,
                              int a_number_of_options,
                              Glib::OptionGroup &a_group) ;
} // namespace Util
} // namespace Glib

#endif //__GLIBMM_UTILS_OPTION_UTILS_H__
