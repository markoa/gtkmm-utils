/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  glibmm-utils - date.cc
 *
 *  Copyright (C) 2007 Marko Anastasov
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

#include "date.h"

#include <sys/time.h>

#include <glib/gmessages.h>

#include <glibmm/convert.h>
#include <glibmm/date.h>

namespace Glib
{

namespace Util
{

namespace
{

static void
get_current_daytime_generic(Glib::ustring& time_str, const char* format)
{
    struct timeval tv;
    struct tm* ptm;

    // Assumed char* length enough for a datetime for any locale's encoding:
    char time_string[124];

    // Obtain the time of day, and convert it to a tm struct.
    gettimeofday(&tv, NULL);
    ptm = localtime(&tv.tv_sec);

    strftime(time_string, sizeof (time_string), format, ptm);

    time_str = Glib::locale_to_utf8(time_string);
}

} // anonymous namespace

void
get_current_time(Glib::ustring& time)
{
    get_current_daytime_generic(time, "%X");
}

void
get_current_date(Glib::ustring& date)
{
    get_current_daytime_generic(date, "%x");
}

void
get_current_datetime(Glib::ustring& datetime)
{
    get_current_daytime_generic(datetime, "%c");
}

void
get_modification_date(time_t timet, Glib::ustring& date_str)
{
    // TODO: translate these strings

    Glib::ustring mod_date("Unknown");
  
    Glib::Date mtime;
    mtime.set_time(timet);
  
    time_t time_now;
    time_now = time(0);
    Glib::Date now;
    now.set_time(time_now);
	
    int days_diff = now.get_julian() - mtime.get_julian();
    Glib::ustring format;
  
    if (days_diff == 0)
    {
        mod_date = "Today";
    }
    else if (days_diff == 1)
    {
        mod_date = "Yesterday";
    }
    else
    {
        if (days_diff > 1 && days_diff < 7)
        {
            format = "%A"; // days from last week
        }
        else
        {
            // any other date, use the locale-preferred representation
            format = "%x";
        }
    
        try
        {
            mod_date = mtime.format_string(format);
        }
        catch (Glib::ConvertError& ex)
        {
            g_warning("Cannot convert file modification time: %s",
                      ex.what().c_str());
        }
    }
  
    if (mod_date.empty()) {
        mod_date = "Unknown";
    }
  
    date_str = mod_date;
}

} // namespace Util

} // namespace Glib
