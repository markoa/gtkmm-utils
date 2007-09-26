/* -*- Mode: C++; indent-tabs-mode:nil; c-basic-offset:4; -*- */

/*
 *  glibmm-utils - date.hh
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

#ifndef __GLIBMM_UTILS_DATE_H__
#define __GLIBMM_UTILS_DATE_H__

#include <glibmm/ustring.h>

namespace Glib {

namespace Util {

/// \brief Returns current time formatted in representation
/// for the current locale.
/// \param date  a string to hold the return value.
void get_current_date(Glib::ustring& date);

/// \brief Returns current date formatted in representation
/// for the current locale.
/// \param time  a string to hold the return value.
void get_current_time(Glib::ustring& time);

/// \brief Returns current date and time formatted in representation
/// for the current locale.
/// \param datetime  a string to hold the return value.
void get_current_datetime(Glib::ustring& datetime);

/// \brief Returns a modification date in GTK+ style.
/// That will be: Today, Yesterday, X ago (if within a week) and,
/// if older, a date formatted according to the current locale.
/// \param timet time information
/// \param date_str Return value: 
void get_modification_date(time_t timet,
                           Glib::ustring& date_str);

} // namespace Util

} // namespace Glib

#endif // __GLIBMM_UTILS_DATE_H__
