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

#include <glib/gmem.h>
#include <glib/gmessages.h>
#include "ustring.h"

namespace Glib {

namespace Util {

using std::vector;

vector<Glib::ustring>
split(const Glib::ustring& str, const Glib::ustring& delim)
{
    vector<Glib::ustring> result;

    if (str.size () == Glib::ustring::size_type(0)) { return result; }

    int len = str.size () + 1;

    gchar* buf = (gchar*) g_malloc (len);
    memset (buf, 0, len);
    memcpy (buf, str.c_str (), str.size ());

    gchar** splited = g_strsplit (buf, delim.c_str (), -1);

    try {
        for (gchar **cur = splited ; cur && *cur; ++cur) {
            result.push_back (Glib::ustring (*cur));
        }
    } catch (...) {}

    if (splited) {
        g_strfreev (splited);
    }

    g_free (buf);

    return result;
}

vector<Glib::ustring>
split(const Glib::ustring& str)
{
    vector<Glib::ustring> res;

    int bytes = str.bytes ();

    g_return_val_if_fail (bytes != Glib::ustring::size_type (0), res);
    g_return_val_if_fail (str.validate(), res);

    // dive into C to strip leading or trailing whitespace
    gchar* buf = g_new0 (gchar, bytes + 1);
    memcpy (buf, str.c_str (), bytes);

    gchar* stripped = g_strdup (buf);
    stripped = g_strstrip (stripped);
    g_free (buf);
    if (g_utf8_strlen (stripped, -1) == 0) {
        g_free (stripped);
        return res;
    }

    // start splitting
    Glib::ustring tmp (stripped);
    g_free (stripped);

    Glib::ustring::size_type chars = str.size ();
    Glib::ustring::size_type i, tail;
    i = 0;
    tail = 1;

    while (tail <= chars) {
        gunichar ch = tmp[tail];

        if ((g_unichar_isspace (ch) == TRUE) || (tail == chars)) {
            int chars_to_skip = 1;
            int pos;
            bool in_ws = true;

            while (in_ws) {
                pos = tail + chars_to_skip;
                ch = tmp[pos];
                (g_unichar_isspace (ch)) ? ++chars_to_skip : in_ws = false;
            }

            if (tail == chars) ++tail;

            res.push_back (tmp.substr (i, tail - i));

            i = tail + chars_to_skip;
            tail += chars_to_skip + 1;
        }

        ++tail;
    }

    return res;
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

