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

#include <tr1/memory>
#include <glib/gmem.h>
#include "ustring.hh"

namespace Glib {

namespace Util {

std::vector<Glib::ustring>
split(const Glib::ustring& str, const Glib::ustring& delim)
{
    std::vector<Glib::ustring> result;

    if (str.size () == Glib::ustring::size_type(0)) { return result; }

    int len = str.size () + 1;

    std::tr1::shared_ptr<gchar> buf (new gchar[len]);
    memset (buf.get (), 0, len);
    memcpy (buf.get (), str.c_str (), str.size ());

    gchar **splited = g_strsplit (buf.get (), delim.c_str (), -1);

    try {
        for (gchar **cur = splited ; cur && *cur; ++cur) {
            result.push_back (Glib::ustring (*cur));
        }
    } catch (...) {}

    if (splited) {
        g_strfreev (splited);
    }

    return result;
}

void
trim_left(Glib::ustring& str)
{
    Glib::ustring::iterator it(str.begin());
    Glib::ustring::iterator end(str.end());

    for ( ; it != end; ++it)
        if (! isspace(*it))
            break;

    if (it == str.end())
        str.clear();
    else
        str.erase(str.begin(), it);
}

void
trim_right(Glib::ustring& str)
{
    typedef Glib::ustring::iterator ustring_iter;

    ustring_iter end(str.end());
    ustring_iter it(--(str.end()));

    for ( ; ; --it) {
        if (! isspace(*it)) {
            ustring_iter it_adv(it);
            str.erase(++it_adv, str.end());
            break;
        }

        if (it == str.begin()) {
            str.clear();
            break;
        }
    }
}

void
trim(Glib::ustring& str)
{
    trim_left(str);
    trim_right(str);
}

Glib::ustring
uprintf(const Glib::ustring& format, ...)
{
    va_list args;

    va_start(args, format);
    gchar* cstr = g_strdup_vprintf(format.c_str(), args);
    Glib::ustring str(cstr);
    g_free(cstr);
  
    return str;
}

} // namespace Util

} // namespace Glib

